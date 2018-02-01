#include "STGParticleLayer.h"

STGParticleLayer::STGParticleLayer() : Layer(32,16,384,448)
{
	Ptr<Camera3D> camera = Ptr<Camera3D>::New();
	camera->SetPosition(Vector3f(192, 224, -200));
	camera->SetLookAt(Vector3f(192, 224, 0));
	camera->SetUp(Vector3f(0, 1, 0));

	SetFirstCamera(camera.Get());
}

STGParticleLayer::~STGParticleLayer()
{

}