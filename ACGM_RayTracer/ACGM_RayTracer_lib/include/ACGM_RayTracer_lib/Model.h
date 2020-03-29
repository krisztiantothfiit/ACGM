#pragma once

#include <ACGM_RayTracer_lib/Ray.h>
#include <ACGM_RayTracer_lib/HitResult.h>
#include <ACGM_RayTracer_lib/Shader.h>
#include <optional>

namespace acgm
{
  //! Model  - abstract base class for scene models
  class Model
  {
  public:
    //! Model constructor - abstract
    explicit Model();
    //! Model constructor
    virtual ~Model() = default;
    //! Model intersection with ray - abstract
    virtual std::optional<HitResult> Intersect(const acgm::Ray& ray) const;
    //! Get Model shader
    std::shared_ptr<acgm::Shader> GetShader() const;
    //! Set Model shader
    void SetShader(const std::shared_ptr<acgm::Shader> shader);
    //! Model name
    std::string name;

  private:
      //! Shader of the model
      std::shared_ptr<acgm::Shader> shader_;
  };
}
