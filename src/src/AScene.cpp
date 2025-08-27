#include "AScene.h"

#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdio>
#include <glm/glm.hpp>

/**
 * <summary>
 * Écrit un vecteur 3D au format JSON.
 * </summary>
 */
static void WriteVec3(std::ostream& os, const glm::vec3& v)
{
    os << "[" << v.x << "," << v.y << "," << v.z << "]";
}

/**
 * <summary>
 * Convertit une chaîne JSON en vecteur 3D.
 * </summary>
 */
static glm::vec3 ParseVec3(const std::string& data)
{
    glm::vec3 v{0.0f};
    std::sscanf(data.c_str(), "[%f,%f,%f]", &v.x, &v.y, &v.z);
    return v;
}

namespace NNE {

/**
 * <summary>
 * Détruit toutes les entités contenues dans la scène.
 * </summary>
 */
AScene::~AScene()
{
    for (AEntity* e : entities)
        delete e;
    entities.clear();
}

/**
 * <summary>
 * Sauvegarde la scène dans un fichier JSON minimal.
 * </summary>
 */
bool AScene::Save(const std::string& path) const
{
    std::ofstream file(path);
    if (!file.is_open())
        return false;

    file << "{\n  \"entities\": [\n";
    for (size_t i = 0; i < entities.size(); ++i) {
        const AEntity* entity = entities[i];
        file << "    {\n      \"components\": [\n";

        bool first = true;
        for (NNE::Component::AComponent* comp : entity->components) {
            if (!first) file << ",\n";
            first = false;

            if (auto* t = dynamic_cast<NNE::Component::TransformComponent*>(comp)) {
                file << "        {\"type\":\"TransformComponent\",";
                file << "\"position\":"; WriteVec3(file, t->position); file << ",";
                file << "\"rotation\":"; WriteVec3(file, t->rotation); file << ",";
                file << "\"scale\":"; WriteVec3(file, t->scale); file << "}";
            } else if (auto* m = dynamic_cast<NNE::Component::Render::MeshComponent*>(comp)) {
                file << "        {\"type\":\"MeshComponent\",";
                file << "\"model\":\"" << m->GetModelPath() << "\",";
                file << "\"texture\":\"" << m->GetTexturePath() << "\"}";
            }
        }
        file << "\n      ]\n    }";
        if (i + 1 < entities.size())
            file << ",";
        file << "\n";
    }
    file << "  ]\n}\n";

    return true;
}

/**
 * <summary>
 * Charge la scène à partir d'un fichier JSON minimal.
 * </summary>
 */
bool AScene::Load(const std::string& path)
{
    std::ifstream file(path);
    if (!file.is_open())
        return false;

    for (AEntity* e : entities)
        delete e;
    entities.clear();

    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    size_t pos = content.find("\"entities\"");
    if (pos == std::string::npos) return false;
    pos = content.find("[", pos);
    if (pos == std::string::npos) return false;

    while (true) {
        pos = content.find("\"components\"", pos);
        if (pos == std::string::npos) break;
        pos = content.find("[", pos);
        if (pos == std::string::npos) break;
        ++pos;

        AEntity* entity = new AEntity();
        entities.push_back(entity);

        while (pos < content.size() && content[pos] != ']') {
            pos = content.find("\"type\"", pos);
            if (pos == std::string::npos) break;
            size_t q1 = content.find('"', pos + 6);
            size_t q2 = content.find('"', q1 + 1);
            std::string type = content.substr(q1 + 1, q2 - q1 - 1);
            pos = q2 + 1;

            if (type == "TransformComponent") {
                size_t pBegin = content.find('[', content.find("\"position\"", pos));
                size_t pEnd = content.find(']', pBegin);
                glm::vec3 p = ParseVec3(content.substr(pBegin, pEnd - pBegin + 1));

                size_t rBegin = content.find('[', content.find("\"rotation\"", pEnd));
                size_t rEnd = content.find(']', rBegin);
                glm::vec3 r = ParseVec3(content.substr(rBegin, rEnd - rBegin + 1));

                size_t sBegin = content.find('[', content.find("\"scale\"", rEnd));
                size_t sEnd = content.find(']', sBegin);
                glm::vec3 s = ParseVec3(content.substr(sBegin, sEnd - sBegin + 1));

                NNE::Component::TransformComponent* t = entity->AddComponent<NNE::Component::TransformComponent>();
                t->position = p;
                t->rotation = r;
                t->scale = s;
                pos = sEnd + 1;
            } else if (type == "MeshComponent") {
                size_t mBegin = content.find('"', content.find("\"model\"", pos) + 7);
                size_t mEnd = content.find('"', mBegin + 1);
                std::string model = content.substr(mBegin + 1, mEnd - mBegin - 1);

                size_t tBegin = content.find('"', content.find("\"texture\"", mEnd) + 9);
                size_t tEnd = content.find('"', tBegin + 1);
                std::string texture = content.substr(tBegin + 1, tEnd - tBegin - 1);

                NNE::Component::Render::MeshComponent* m = entity->AddComponent<NNE::Component::Render::MeshComponent>();
                m->SetModelPath(model);
                m->SetTexturePath(texture);
                pos = tEnd + 1;
            }

            pos = content.find_first_of(",]", pos);
            if (pos == std::string::npos) break;
            if (content[pos] == ',') ++pos;
        }

        pos = content.find(']', pos);
        if (pos == std::string::npos) break;
    }

    return true;
}

} // namespace NNE

