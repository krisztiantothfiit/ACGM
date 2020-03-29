#include "RayTracerResource.h"
#include "RayTracerGadget.h"
#include <ACGM_RayTracer_lib\SceneImporter.h>

RayTracerGadget::RayTracerGadget(const hiro::Resource *res)
  : hiro::Gadget(res)
{
}

void RayTracerGadget::Initialize()
{
  hiro::Gadget::Initialize();
  style_ = std::make_shared<hiro::draw::RasterStyle>();
  style_->use_nearest_filtering = true;
  AddRenderer(GetResource<RayTracerResource>()->GetRenderer(), style_);
  acgm::SceneImporter scene_importer;
  scene_importer.Import("scene0.txt");
  std::shared_ptr<acgm::Scene> imported_scene = scene_importer.GetScene();
  auto renderer = GetResource<RayTracerResource>()->GetRenderer();
  renderer->SetResolution({ scene_importer.GetRenderOptions().resolution.x, scene_importer.GetRenderOptions().resolution.y });
  imported_scene->Raytrace(renderer);
}

void RayTracerGadget::GenerateGui(hiro::GuiGenerator& gui) {
    hiro::Gadget::GenerateGui(gui);
    hiro::gui::Droplist* sceneFile;

    sceneFile = gui.AddDroplist("Scene File")->AddItemsIndexed({ "scene0.txt", "scene1.txt", "scene2.txt" })->Set(0);

    gui.AddButton("Import and Render")->Subscribe([this, sceneFile](const hiro::gui::Button* button) {
        acgm::SceneImporter scene_importer;
        scene_importer.Import(sceneFile->GetText());
        std::shared_ptr<acgm::Scene> imported_scene = scene_importer.GetScene();
        auto renderer = GetResource<RayTracerResource>()->GetRenderer();
        renderer->SetResolution({ scene_importer.GetRenderOptions().resolution.x, scene_importer.GetRenderOptions().resolution.y });
        imported_scene->Reset(renderer);
        imported_scene->Raytrace(renderer);
    });
}

