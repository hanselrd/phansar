#include <phansar/client/graphics/model.hpp>
#include <phansar/common/macros.hpp>

namespace phansar::client::graphics {
model::model(std::string_view _file_path) {
    auto         importer = Assimp::Importer{};
    const auto * scene =
        importer.ReadFile(std::string{_file_path}, aiProcessPreset_TargetRealtime_Fast);

    PH_ASSERT_ALWAYS(scene && ! (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) && scene->mRootNode);

    for (auto i = std::size_t{0}; i < scene->mNumMeshes; ++i) {
        auto * mesh = scene->mMeshes[i];

        /* glm::vec3 ambient; */
        /* glm::vec3 diffuse; */
        /* glm::vec3 specular; */
        /* float shininess; */
        auto * material = scene->mMaterials[mesh->mMaterialIndex];
        /* auto ambient = aiColor4D{}; */
        /* auto diffuse = aiColor4D{}; */
        /* auto specular = aiColor4D{}; */
        /* auto shininess = float{}; */
        /* aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &ambient); */
        /* aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &diffuse); */
        /* aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &specular); */
        /* aiGetMaterialFloat(material, AI_MATKEY_COLOR_SHININESS, &shininess); */
        /* if (material->GetTextureCount(aiTextureType_DIFFUSE)) { */
        /* auto path = aiString{}; */
        /* if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, nullptr, nullptr, nullptr,
         * nullptr, nullptr) == AI_SUCCESS) { */
        /* } */
        /* } */

        auto vertices = std::vector<vertex>{};
        for (auto j = std::size_t{0}; j < mesh->mNumVertices; ++j) {
            auto position =
                glm::vec3{mesh->mVertices[j].x, mesh->mVertices[j].y, mesh->mVertices[j].z};

            auto normal = glm::vec3{};
            if (mesh->HasNormals()) {
                normal = glm::vec3{mesh->mNormals[j].x, mesh->mNormals[j].y, mesh->mNormals[j].z};
            }

            auto tangent   = glm::vec3{};
            auto bitangent = glm::vec3{};
            if (mesh->HasTangentsAndBitangents()) {
                tangent =
                    glm::vec3{mesh->mTangents[j].x, mesh->mTangents[j].y, mesh->mTangents[j].z};
                bitangent = glm::vec3{mesh->mBitangents[j].x,
                                      mesh->mBitangents[j].y,
                                      mesh->mBitangents[j].z};
            }

            auto texcoord0 = glm::vec2{};
            if (mesh->HasTextureCoords(0) &&
                (material->GetTextureCount(aiTextureType_DIFFUSE) != 0)) {
                texcoord0 = glm::vec2{mesh->mTextureCoords[0][j].x, mesh->mTextureCoords[0][j].y};
            }

            vertices.push_back(vertex{.position{position},
                                      .normal{normal},
                                      .tangent{tangent},
                                      .bitangent{bitangent},
                                      .texcoord0{texcoord0}});
        }

        auto indices = std::vector<std::uint32_t>{};
        for (auto j = std::size_t{0}; j < mesh->mNumFaces; ++j) {
            auto face = mesh->mFaces[j];
            PH_ASSERT(face.mNumIndices == 3);
            indices.push_back(face.mIndices[0]);
            indices.push_back(face.mIndices[1]);
            indices.push_back(face.mIndices[2]);
        }

        m_meshes.emplace_back(vertices, indices);
    }
}

auto model::meshes() const -> const std::vector<mesh> & {
    PH_ASSERT(! m_meshes.empty());

    return m_meshes;
}

auto model::materials() const -> const std::vector<material> & {
    PH_ASSERT(! m_materials.empty());

    return m_materials;
}
} // namespace phansar::client::graphics
