#include "Stage01.h"
#include "../Enemy/Stage01/Enemy01_001.h"
#include "../Enemy/Stage01/Enemy01_002.h"
#include "../Enemy/Stage01/Enemy01_003.h"

Texture* Stage01::texRoad = nullptr;

const int Stage01::BPM = 120;
const float Stage01::SPB = 60.0f / BPM;
const float Stage01::FPB = 60.0f * SPB;

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
	AddEnemy001(0);
	AddEnemy002(120);
	AddEnemy001(240);
	AddEnemy002(360);
	AddEnemy003(500);
}

void Stage01::AddEnemy001(int startFrame)
{
	auto engine = STGEngine::GetInstance();
	int frame2 = frame - startFrame;
	const int interval = 30;
	if (frame2 < 80 && frame2 % 10 == 1)   //frame == 1,11,21,...71
	{
		int i = frame2 / 10;
		Enemy01_001* enemy = new Enemy01_001();
		enemy->SetPosition(-30, 420);
		TweenSequence* sequence = new TweenSequence();
		sequence->AddTween(new MoveTo(Vector3f(192 + interval * (3.5f - i), 280, enemy->GetPosition().z), 120, Tweener::EASE_OUT));
		sequence->AddTween(new Delay(60));
		sequence->AddTween(new MoveTo(Vector3f(420, 140, enemy->GetPosition().z), 120, Tweener::EASE_IN));
		enemy->AddTween(sequence);
		engine->AddEnemy(enemy);
	}
}

void Stage01::AddEnemy002(int startFrame)
{
	auto engine = STGEngine::GetInstance();
	int frame2 = frame - startFrame;
	const int interval = 30;
	if (frame2 < 80 && frame2 % 10 == 1)   //frame == 1,11,21,...71
	{
		int i = frame2 / 10;
		Enemy01_002* enemy = new Enemy01_002();
		enemy->SetPosition(414, 420);
		TweenSequence* sequence = new TweenSequence();
		sequence->AddTween(new MoveTo(Vector3f(192 + interval * (i - 3.5), 280, enemy->GetPosition().z), 120, Tweener::EASE_OUT));
		sequence->AddTween(new Delay(60));
		sequence->AddTween(new MoveTo(Vector3f(-36, 140, enemy->GetPosition().z), 120, Tweener::EASE_IN));
		enemy->AddTween(sequence);
		engine->AddEnemy(enemy);
	}
}

void Stage01::AddEnemy003(int startFrame)
{
	auto engine = STGEngine::GetInstance();
	if (frame == startFrame)
	{
		Enemy01_003* enemy = new Enemy01_003();
		enemy->SetPosition(192, 500);
		TweenSequence* sequence = new TweenSequence();
		sequence->AddTween(new MoveTo(Vector3f(192, 320, enemy->GetPosition().z), 120, Tweener::SIMPLE));
		sequence->AddTween(new Delay(500));
		sequence->AddTween(new MoveTo(Vector3f(192, 500, enemy->GetPosition().z), 180, Tweener::SIMPLE));
		enemy->AddTween(sequence);
		engine->AddEnemy(enemy);
	}
}

void Stage01::OnStart()
{
	Stage::OnStart();

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

	this->SetBGM(Audio::GetInstance()->CreateMusic("bgm/stage01.wav"));
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