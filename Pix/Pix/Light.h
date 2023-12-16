#pragma once

#include "MathHelper.h"
#include <XEngine.h>


class Light
{
public:
    virtual ~Light() = default;

    virtual X::Color ComputeLightColor(const Vec3& position, const Vec3& normal) = 0;
    
    //is color without lighting
    void SetAmbient(const X::Color& ambient) { mAmbient = ambient; }
    //is color with lighting
    void SetDiffuse(const X::Color& diffuse) { mDiffuse = diffuse; }
    //enhanced color at lighting focal point
    void SetSpecular(const X::Color& specular) { mSpecular = specular; }
protected:
    X::Color mAmbient = X::Colors::White;
    X::Color mDiffuse = X::Colors::White;
    X::Color mSpecular = X::Colors::White;
};

