#pragma once

#include "Runtime/Renderer/Texture.h"
#include "Runtime/Renderer/Shader.h"
#include "Runtime/Library/ShaderLibrary.h"
#include "Runtime/Library/TextureLibrary.h"

#include <unordered_map>

namespace X
{
    struct EnumClassHash
    {
        template <typename T>
        std::size_t operator()(T t) const
        {
            return static_cast<std::size_t>(t);
        }
    };

    enum class Mat_TextureType
    {
        Albedo = 0,
        Normal,
        Metalness,
        Roughness,
        AmbientOcclusion,
        Specular,
        Height,
        Emission,
    };

    struct MaterialTexture
    {
        Ref<Texture2D> texture2d = nullptr;
        Mat_TextureType type;
        std::string path;
    };

    class Material
    {
    public:
        Material() { Initialize(); };
        Material(Ref<Shader> shader) : mShader(shader) { Initialize(); };
    public:
        void SetShader(Ref<Shader> shader) { mShader = shader; }
        [[nodiscard]] Ref<Shader> GetShader() { return mShader; }

        void AddTexture(Mat_TextureType type, Ref<Texture2D> texture)
        {
            X_CORE_ASSERT(mTexMap.find(type) == mTexMap.end());
            mTexMap[type] = texture;
        }

        [[nodiscard]] Ref<Texture2D> GetTexture(Mat_TextureType type) { return mTexMap[type]; }

        void LoadTextures();
    private:
        void Initialize();
    public:
        std::vector<MaterialTexture> mTextures;

        std::string defaultTexPath = "Assets/Textures/DefaultTexture.png";

        bool bUseAlbedoMap = false;
        glm::vec4 col = { 1.0f, 1.0f, 1.0f, 1.0f }; // 0 ~ 1
        Ref<Texture2D> albedoRGBA = Texture2D::Create(1, 1);
        Ref<Texture2D> mAlbedoMap = Library<Texture2D>::GetInstance().GetDefaultTexture();
        std::string mAlbedoMapPath ;

        bool bUseNormalMap = false;
        Ref<Texture2D> mNormalMap = Library<Texture2D>::GetInstance().Get("DefaultNormal");
        std::string mNormalMapPath;

        bool bUseMetallicMap = false;
        float metallic = 0.1f;
        Ref<Texture2D> metallicRGBA = Texture2D::Create(1, 1);
        Ref<Texture2D> mMetallicMap = Library<Texture2D>::GetInstance().Get("DefaultMetallicRoughness");
        std::string mMetallicMapPath ;

        bool bUseRoughnessMap = false;
        float roughness = 0.9f;
        Ref<Texture2D> roughnessRGBA = Texture2D::Create(1, 1);
        Ref<Texture2D> mRoughnessMap = Library<Texture2D>::GetInstance().Get("DefaultMetallicRoughness");
        std::string mRoughnessMapPath ;

        bool bUseAoMap = false;
        Ref<Texture2D> mAoMap = Library<Texture2D>::GetInstance().GetWhiteTexture();
        std::string mAoMapPath;

    private:
        Ref<Shader> mShader;
        std::unordered_map<Mat_TextureType, Ref<Texture2D>, EnumClassHash> mTexMap;
    };
}