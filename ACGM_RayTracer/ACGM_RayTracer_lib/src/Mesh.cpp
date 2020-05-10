#include <ACGM_RayTracer_lib/Mesh.h>
#include <COGS\Mesh.h>

cogs::Mesh mesh;

acgm::Mesh::Mesh(std::string file_name, glm::mat4 transform)
{
    mesh.Import(file_name);
    mesh.points->Transform(transform);
}

std::optional<acgm::HitResult> acgm::Mesh::Intersect(const acgm::Ray& ray)
{
    float t = -INFINITY;
    float minT = INFINITY;
    glm::vec3 v0v1;
    glm::vec3 v0v2;
    glm::vec3 v0v1Min;
    glm::vec3 v0v2Min;
    for (unsigned int i = 0; i < mesh.faces->GetFaceCount(); i++) {
        glm::vec3 face = mesh.faces->GetFaces().at(i);
        glm::vec3 v0 = mesh.points->GetPositions()[(int)face.x];
        glm::vec3 v1 = mesh.points->GetPositions()[(int)face.y];
        glm::vec3 v2 = mesh.points->GetPositions()[(int)face.z];

        v0v1 = v1 - v0;
        v0v2 = v2 - v0;

        glm::vec3 pvec = glm::cross(ray.GetDirection(), v0v2);

        float det = glm::dot(v0v1, pvec);

        if (fabs(det) < std::numeric_limits<float>().epsilon())
            continue;

        float invDet = 1.0f / det;

        glm::vec3 tvec = ray.GetOrigin() - v0;

        float u = glm::dot(tvec, pvec) * invDet;

        if (u < 0 || u > 1)
            continue;

        glm::vec3 qvec = glm::cross(tvec, v0v1);

        float v = glm::dot(ray.GetDirection(), qvec) * invDet;

        if (v < 0 || u + v > 1)
            continue;

        t = glm::dot(v0v2, qvec) * invDet;

        if (glm::isinf(t) || t < 0.0f)
        {
            continue;
        }

        if (t < minT) {
            minT = t;
            v0v1Min = v0v1;
            v0v2Min = v0v2;
        }
    }

    if (minT == INFINITY) {
        return std::nullopt;
    }

    HitResult hit;
    hit.SetRayParam(minT);
    hit.SetRayNormal(glm::normalize(glm::cross(v0v1Min, v0v2Min)));
    return hit;
}
