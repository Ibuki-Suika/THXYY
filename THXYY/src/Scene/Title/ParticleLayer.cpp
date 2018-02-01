#include "ParticleLayer.h"
#include "SakuraParticle.h"

ParticleLayer::ParticleLayer()
{
}

ParticleLayer::~ParticleLayer()
{
}

void ParticleLayer::SetupCamera()
{
	Ptr<Camera3D> camera = Ptr<Camera3D>::New();
	camera->SetPosition(Vector3f(320, 240, -300));
	camera->SetLookAt(Vector3f(320, 240, 0));
	camera->SetUp(Vector3f(0, 1, 0));

	SetFirstCamera(camera.Get());
}

void ParticleLayer::OnStart()
{
	Layer::OnStart();

	SetupCamera();
}

void ParticleLayer::Update()
{
	Layer::Update();

	frame++;

	if (frame == 20)
	{
		frame = 0;
		AddParticle();
	}
}

void ParticleLayer::AddParticle()
{
	Ptr<SakuraParticle> particle = Ptr<SakuraParticle>::New(0);

	particle->SetLife(300);

	float x = Math::Random(-100, 740);
	float y = Math::Random(360, 500);
	float z = Math::Random(0, 100);
	particle->SetPosition(Vector3f(x, y, z));

	float rad = Math::ToRad(Math::Random(0, 90) + 225);
	particle->SetDirection(Vector3f(cos(rad), sin(rad), 0));

	particle->SetRotatingAxis(Vector3f(Math::Random(-100, 100), Math::Random(-100, 100), Math::Random(-100, 100)));
	particle->SetRotatingSpeed(Math::Random(100, 500) / 100.0f);
	particle->SetSpeed(0.5f + Math::Random(0, 100) / 100.0f);
	particle->SetAlpha(0);

	Ptr<TweenSequence> sequence = Ptr<TweenSequence>::New();
	sequence->AddTween(Ptr<FadeTo>::New(0.6f, 100, Tweener::EASE_OUT).Get());
	sequence->AddTween(Ptr<Delay>::New(100).Get());
	sequence->AddTween(Ptr<FadeOut>::New(100, Tweener::EASE_OUT).Get());
	particle->AddTween(sequence.Get());

	AddChild(particle.Get());
}