#include "DepthBuffer.h"

DepthBuffer* DepthBuffer::Get()
{
	static DepthBuffer sInstance;
	return &sInstance;
}

void DepthBuffer::OnNewFrame()
{
	mEnabled = false;
	for (size_t i = 0; i < mWidth; ++i)
	{
		mDepthBuffer[i] = 1.0f;
	}
}

void DepthBuffer::Initialize(int width, int height)
{
	if (width != mWidth && height != mHeight)
	{
		mDepthBuffer = std::make_unique<float[]>(width * height);
		mWidth = width;
		mHeight = height;
		OnNewFrame();
	}
}

void DepthBuffer::SetEnabled(bool enabled)
{
}

void DepthBuffer::CheckDepthBuffer(int x, int y, float depth)
{
}
