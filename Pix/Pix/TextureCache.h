#pragma once
#include "Texture.h"

class TextureCache
{
public:
	static TextureCache* Get();

	void Clear();
	void SetTexture(const std::string& fileName);
	void SetUseFilter(bool useFilter);
	void SetAddressMode(AddressMode mode);

	X::Color SampleColor(const X::Color& uv) const;

private:
	std::vector<std::unique_ptr<Texture>> mTextures;
	const Texture* mCurrentTexture = nullptr;
	bool mUseFilter = false;
	AddressMode mAddressMode = AddressMode::Clamp;
};