#ifndef MATERIAL_HPP
#define MATERIAL_HPP

class Material
{
// examples: color, lighting_enabled, do_alpha_blend, texture, list of textures, vertex/fragment shader program!!!

private:
    Material() {}; // default constructor

public:
    Material(const char* filename);
};


#endif
