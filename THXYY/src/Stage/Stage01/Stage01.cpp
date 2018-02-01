#include "Stage01.h"
#include "../Enemy/Stage01/Enemy01_001.h"
#include "../Enemy/Stage01/Enemy01_002.h"
#include "../Enemy/Stage01/Enemy01_003.h"

const int Stage01::BPM = 120;
const float Stage01::SPB = 60.0f / BPM;
const float Stage01::FPB = 60.0f * SPB;

Stage01::Stage01()
{
}

Stage01::~Stage01()
{
	auto assetManager = AssetManager::GetInstance();
}

void Stage01::Update()
{
	Stage::Update();

	auto engine = STGEngine::GetInstance();

	frame++;
	AddEnemy001(1);
	AddEnemy002(5.5 * FPB);
	AddEnemy001(10 * FPB);
	AddEnemy002(14.5 * FPB);
	AddEnemy003(19 * FPB);

	ShowLogo(40.5 * FPB);
}

void Stage01::ShowLogo(int startFrame)
{
	auto engine = STGEngine::GetInstance();

	if (frame == startFrame)
	{
		Ptr<Sprite> logo = Ptr<Sprite>::New();
		logo->SetTexture(this->texLogo);
		logo->SetPosition(Vector3f(192, 280, 10));
		logo->SetAlpha(0.0f);
		Ptr<TweenSequence> sequence = Ptr<TweenSequence>::New();
		sequence->AddTween(Ptr<FadeTo>::New(1.0f, 80, Tweener::SIMPLE).Get());
		sequence->AddTween(Ptr<Delay>::New(240).Get());
		sequence->AddTween(Ptr<FadeOut>::New(80, Tweener::SIMPLE).Get());
		logo->AddTween(sequence.Get());
		engine->AddObject(logo);
	}
}

void Stage01::AddEnemy001(int startFrame)
{
	auto engine = STGEngine::GetInstance();
	int frame2 = frame - startFrame;
	const int interval = 30;
	if (frame2 < 80 && frame2 % 10 == 1)   //frame == 1,11,21,...71
	{
		int i = frame2 / 10;
		Ptr<Enemy01_001> enemy = Ptr<Enemy01_001>::New();
		enemy->SetPosition(-30, 420);
		Ptr<TweenSequence> sequence = Ptr<TweenSequence>::New();
		sequence->AddTween(Ptr<MoveTo>::New(Vector3f(192 + interval * (3.5f - i), 280, 
			enemy->GetPosition().z), 120, Tweener::EASE_OUT).Get());
		sequence->AddTween(Ptr<Delay>::New(60).Get());
		sequence->AddTween(Ptr<MoveTo>::New(Vector3f(420, 140, enemy->GetPosition().z), 120, Tweener::EASE_IN).Get());
		enemy->AddTween(sequence.Get());
		engine->AddEnemy(enemy.Get());
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
		Ptr<Enemy01_002> enemy = Ptr<Enemy01_002>::New();
		enemy->SetPosition(414, 420);
		Ptr<TweenSequence> sequence = Ptr<TweenSequence>::New();
		sequence->AddTween(Ptr<MoveTo>::New(Vector3f(192 + interval * (i - 3.5), 280, 
			enemy->GetPosition().z), 120, Tweener::EASE_OUT).Get());
		sequence->AddTween(Ptr<Delay>::New(60).Get());
		sequence->AddTween(Ptr<MoveTo>::New(Vector3f(-36, 140, enemy->GetPosition().z), 120, Tweener::EASE_IN).Get());
		enemy->AddTween(sequence.Get());
		engine->AddEnemy(enemy.Get());
	}
}

void Stage01::AddEnemy003(int startFrame)
{
	auto engine = STGEngine::GetInstance();
	if (frame == startFrame)
	{
		Ptr<Enemy01_003> enemy = Ptr<Enemy01_003>::New();
		enemy->SetPosition(192, 500);
		Ptr<TweenSequence> sequence = Ptr<TweenSequence>::New();
		sequence->AddTween(Ptr<MoveTo>::New(Vector3f(192, 320, enemy->GetPosition().z), 120, Tweener::SIMPLE).Get());
		sequence->AddTween(Ptr<Delay>::New(500).Get());
		sequence->AddTween(Ptr<MoveTo>::New(Vector3f(192, 500, enemy->GetPosition().z), 180, Tweener::SIMPLE).Get());
		enemy->AddTween(sequence.Get());
		engine->AddEnemy(enemy.Get());
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

	texLogo = assetManager->CreateTextureFromFile("res/front/logo/stage01_logo.png");
	if (texLogo == nullptr)
	{
		THMessageBox(ExceptionManager::GetInstance()->GetException()->GetInfo());
	}

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

	house = Mesh::CreateMeshFromFile("res/model/house/house.x");
	if (house == nullptr)
	{
		THMessageBox(ExceptionManager::GetInstance()->GetException()->GetInfo());
	}

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
	background->AddLight(Ptr<DirectionalLight>::New(Vector3f(1.8f, 1.8f, 1.8f), Vector3f(1.0f, -1.0f, 0.0f)).Get());

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

	Ptr<Camera3D> camera = Ptr<Camera3D>::New();
	camera->SetPosition(Vector3f(0, 500, 0));
	camera->SetUp(Vector3f(0, 1, 0));
	camera->SetLookAt(Vector3f(0, 500, 10000));
	camera->SetFov(65.0f);
	camera->SetZFar(9000);
	engine->SetBackgroundCamera(camera.Get());
}

void Stage01::SetupFog()
{
	auto scene = (GameScene*)(Game::GetInstance()->GetScene().Get());
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

	Ptr<Mesh> road = Ptr<Mesh>::New();
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

	engine->AddBackgroundObject(road.Get());

	CreateHouses();
}

void Stage01::CreateHouses()
{
	auto engine = STGEngine::GetInstance();

	Ptr<Mesh> houseLeft1 = (Mesh*)house->Clone().Get();
	houseLeft1->SetPosition(Vector3f(-800, 395, 1000));
	engine->AddBackgroundObject(houseLeft1.Get());

	Ptr<Mesh> houseRight1 = (Mesh*)house->Clone().Get();
	houseRight1->SetPosition(Vector3f(800, 395, 1000));
	houseRight1->SetRotationByAxis(Vector3f(0, 1, 0), 180);
	engine->AddBackgroundObject(houseRight1.Get());

	for (int i = 1; i < 5; i++)
	{
		Ptr<Mesh> houseLeft2 = (Mesh*)houseLeft1->Clone().Get();
		houseLeft2->SetPosition(Vector3f(-800, 395, 1000 + 1500 * i));
		engine->AddBackgroundObject(houseLeft2.Get());

		Ptr<Mesh> houseRight2 = (Mesh*)houseRight1->Clone().Get();
		houseRight2->SetPosition(Vector3f(800, 395, 1000 + 1500 * i));
		engine->AddBackgroundObject(houseRight2.Get());
	}
}