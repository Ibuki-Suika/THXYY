#include "Stage01.h"
#include "../Enemy/Stage01/Enemy01_001.h"
#include "../Enemy/Stage01/Enemy01_002.h"
#include "../Enemy/Stage01/Enemy01_003.h"

Texture* Stage01::texRoad = nullptr;

Stage01::Stage01()
{
}

Stage01::~Stage01()
{
	auto assetManager = AssetManager::GetInstance();

	TH_SAFE_RELEASE(texRoad);
	TH_SAFE_RELEASE(sky);

	TH_SAFE_RELEASE(house);
}

void Stage01::Update()
{
	Stage::Update();

	auto engine = STGEngine::GetInstance();

	frame++;

	if (frame == 1 || frame == 50 || frame == 100 || frame == 200)
	{
		Enemy01_001* enemy = new Enemy01_001();
		enemy->SetPosition(-30, 420);
		enemy->AddTween(new MoveTo(Vector3f(192, 280, enemy->GetPosition().z), 180, Tweener::EASE_OUT));
		engine->AddEnemy(enemy);

		Enemy01_002* enemy2 = new Enemy01_002();
		enemy2->AddTween(new MoveTo(Vector3f(192, 300, enemy->GetPosition().z), 240, Tweener::EASE_OUT));
		engine->AddEnemy(enemy2);

		Enemy01_003* enemy3 = new Enemy01_003();
		enemy3->SetPosition(500, 500);
		enemy3->AddTween(new MoveTo(Vector3f(240, 224, enemy->GetPosition().z), 120, Tweener::EASE_OUT));
		engine->AddEnemy(enemy3);
	}
}

void Stage01::OnStart()
{
	InitBackground();
}

void Stage01::OnLoad()
{
	auto assetManager = AssetManager::GetInstance();
	auto engine = STGEngine::GetInstance();

	texRoad = assetManager->CreateTextureFromFile("res/background/stage01/road.jpg");
	if (texRoad == nullptr)
	{
		THMessageBox(ExceptionManager::GetInstance()->GetException()->GetInfo());
	}
	texRoad->Retain();

	sky = assetManager->CreateCubeMapFromFile("res/background/stage01/skybox/BluePinkNebular_front.jpg",
		"res/background/stage01/skybox/BluePinkNebular_back.jpg",
		"res/background/stage01/skybox/BluePinkNebular_left.jpg",
		"res/background/stage01/skybox/BluePinkNebular_right.jpg",
		"res/background/stage01/skybox/BluePinkNebular_top.jpg",
		"res/background/stage01/skybox/BluePinkNebular_bottom.jpg");
	if (sky == nullptr)
	{
		THMessageBox(ExceptionManager::GetInstance()->GetException()->GetInfo());
	}
	sky->Retain();

	house = Mesh::CreateMeshFromFile("res/model/house/house.x");
	if (house == nullptr)
	{
		THMessageBox(ExceptionManager::GetInstance()->GetException()->GetInfo());
	}
	house->Retain();
}

void Stage01::InitBackground()
{
	auto engine = STGEngine::GetInstance();
	auto background = engine->GetGameScene()->GetBackgroundLayer();

	SetupCamera();
	SetupFog();

	background->SetSkyBox(sky);
	background->EnableLighting(true);
	background->SetAmbientLight(Vector4f(0.3f, 0.3f, 0.3f, 1.0f));
	background->AddLight(new DirectionalLight(Vector3f(1.8f, 1.8f, 1.8f), Vector3f(1.0f, -1.0f, 0.0f)));

	InitBackgroundObjects();
}

void Stage01::UpdateBackground()
{
	Stage::UpdateBackground();

	auto engine = STGEngine::GetInstance();
	auto camera = engine->GetBackgroundCamera();

	Vector3f pos = camera->GetPosition();
	float z = pos.z;
	z += 5;
	if (z > 4000)
	{
		z -= 3000;
	}
	pos.z = z;

	camera->SetPosition(pos);
}

void Stage01::SetupCamera()
{
	auto engine = STGEngine::GetInstance();

	Camera3D* camera = new Camera3D();
	camera->SetPosition(Vector3f(0, 500, 0));
	camera->SetUp(Vector3f(0, 1, 0));
	camera->SetLookAt(Vector3f(0, 500, 10000));
	camera->SetFov(65.0f);
	camera->SetZFar(9000);
	engine->SetBackgroundCamera(camera);
}

void Stage01::SetupFog()
{
	auto scene = (GameScene*)(Game::GetInstance()->GetScene());
	auto backgroundLayer = scene->GetBackgroundLayer();

	backgroundLayer->EnableFog(true);

	Fog fog;
	fog.fogColor = Vector4f(0, 0, 0, 1);
	fog.fogStart = 100;
	fog.fogEnd = 3000;
	backgroundLayer->SetFog(fog);
}

void Stage01::InitBackgroundObjects()
{
	auto engine = STGEngine::GetInstance();

	Mesh* road = new Mesh();
	road->InitVertexBuffer(4);

	MeshVertex meshVertices[4] = {
		{ -10000, 0, -10000, 0, 1, 0, -100, -100 },
		{ 10000, 0, -10000, 0, 1, 0, 100, -100 },
		{ -10000, 0, 10000, 0, 1, 0, -100, 100 },
		{ 10000, 0, 10000, 0, 1, 0, 100, 100 }
	};

	road->SetVertexData(meshVertices);
	road->SetPrimitiveType(Mesh::TRIANGLE_STRIP);

	Material roadMaterial;
	roadMaterial.texture = texRoad;

	road->SetMaterial(roadMaterial);

	engine->AddBackgroundObject(road);

	CreateHouses();
}

void Stage01::CreateHouses()
{
	auto engine = STGEngine::GetInstance();

	Mesh* houseLeft1 = (Mesh*)house->Clone();
	houseLeft1->SetPosition(Vector3f(-800, 395, 1000));
	engine->AddBackgroundObject(houseLeft1);

	Mesh* houseRight1 = (Mesh*)house->Clone();
	houseRight1->SetPosition(Vector3f(800, 395, 1000));
	houseRight1->SetRotationByAxis(Vector3f(0, 1, 0), 180);
	engine->AddBackgroundObject(houseRight1);

	for (int i = 1; i < 5; i++)
	{
		Mesh* houseLeft2 = (Mesh*)houseLeft1->Clone();
		houseLeft2->SetPosition(Vector3f(-800, 395, 1000 + 1500 * i));
		engine->AddBackgroundObject(houseLeft2);

		Mesh* houseRight2 = (Mesh*)houseRight1->Clone();
		houseRight2->SetPosition(Vector3f(800, 395, 1000 + 1500 * i));
		engine->AddBackgroundObject(houseRight2);
	}
}