#include "Graphics.h"

#include "Clipper.h"
#include "Viewport.h"
#include "MatrixStack.h"
#include "Camera.h"
#include "PrimitivesManager.h"
#include "DepthBuffer.h"
#include "LightManager.h"
#include "MaterialManager.h"

void Graphics::NewFrame()
{
	Viewport::Get()->OnNewFrame();
	Clipper::Get()->OnNewFrame();
	MatrixStack::Get()->OnNewFrame();
	Camera::Get()->OnNewFrame();
	PrimitivesManager::Get()->OnNewFrame();
	DepthBuffer::Get()->OnNewFrame();
	LightManager::Get()->OnNewFrame();
	MaterialManager::Get()->OnNewFrame();
}