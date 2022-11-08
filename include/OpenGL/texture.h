#pragma once

#include <GLAD/gl.h>

#include <string>

namespace Texture {
enum Format { RGB = GL_RGB, RGBA = GL_RGBA };
enum Filter { NEAREST = GL_NEAREST, LINEAR = GL_LINEAR };
enum Wrap { CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE, CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER, MIRRORED_REPEAT = GL_MIRRORED_REPEAT, REPEAT = GL_REPEAT };

} // namespace Texture

class Texture2D {
private:
  unsigned int m_ID;
  int m_Width;
  int m_Height;
  unsigned char* m_Data;
  Texture::Format m_TextureFormat;
  Texture::Format m_ImageFormat;
  Texture::Filter m_FilterMin;
  Texture::Filter m_FilterMax;
  Texture::Wrap m_WrapR;
  Texture::Wrap m_WrapS;


public:
  Texture2D(int width, int height, unsigned char* data, Texture::Format texturefmt, Texture::Format imagefmt, Texture::Filter min = Texture::Filter::NEAREST,
      Texture::Filter max = Texture::Filter::LINEAR, Texture::Wrap r = Texture::Wrap::CLAMP_TO_EDGE, Texture::Wrap s = Texture::Wrap::CLAMP_TO_EDGE);
  Texture2D();
  ~Texture2D();
  void Generate(unsigned int width, unsigned int height, unsigned char* data);

  void Bind(unsigned int slot = 0) const;
  void Unbind() const;

  unsigned int GetID() const;

  void SetTextureFormat(Texture::Format format);
  void SetImageFormat(Texture::Format format);
};
