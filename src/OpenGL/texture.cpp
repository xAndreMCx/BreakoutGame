#include "OpenGL/texture.h"

#include "OpenGL/debug.h"

Texture2D::Texture2D() : m_ID(0) {}
Texture2D::Texture2D(int width, int height, unsigned char* data, Texture::Format texturefmt, Texture::Format imagefmt, Texture::Filter min, Texture::Filter max,
    Texture::Wrap r, Texture::Wrap s)
    : m_ID(0),
      m_Width(width),
      m_Height(height),
      m_Data(data),
      m_TextureFormat(texturefmt),
      m_ImageFormat(imagefmt),
      m_FilterMin(min),
      m_FilterMax(max),
      m_WrapR(r),
      m_WrapS(s) {
  GLCallV(glGenTextures(1, &m_ID));
  GLCallV(glBindTexture(GL_TEXTURE_2D, m_ID));

  GLCallV(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_FilterMin));
  GLCallV(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_FilterMax));
  GLCallV(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, m_WrapR));
  GLCallV(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_WrapS));

  GLCallV(glTexImage2D(GL_TEXTURE_2D, 0, m_TextureFormat, m_Width, m_Height, 0, m_ImageFormat, GL_UNSIGNED_BYTE, m_Data));

  GLCallV(glBindTexture(GL_TEXTURE_2D, 0));
}

Texture2D::~Texture2D() {} // GLCallV(glDeleteTextures(1, &m_ID));

void Texture2D::Bind(unsigned int slot) const {
  GLCallV(glActiveTexture(GL_TEXTURE0 + slot));
  GLCallV(glBindTexture(GL_TEXTURE_2D, m_ID));
}

void Texture2D::Unbind() const { GLCallV(glBindTexture(GL_TEXTURE_2D, 0)); }

unsigned int Texture2D::GetID() const { return m_ID; }

void Texture2D::SetTextureFormat(Texture::Format format) { m_TextureFormat = format; }
void Texture2D::SetImageFormat(Texture::Format format) { m_ImageFormat = format; }