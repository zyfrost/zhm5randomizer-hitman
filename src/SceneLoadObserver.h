#ifndef __ZHM5RANDOMIZER_SRC_SCENELOADOBSERVER_H__
#define __ZHM5RANDOMIZER_SRC_SCENELOADOBSERVER_H__

#include <functional>

#include "SSceneInitParameters.h"

using tLoadScene =
    uint64_t(__fastcall*)(void* this_, SSceneInitParameters* scene_init_params);
using tLoadSceneCallback = std::function<void(const SSceneInitParameters*)>;

typedef void(__fastcall* tLoad)(void* this_,
                                SSceneInitParameters* scene_init_params);

class SceneLoadObserver {
 private:
  static tLoadScene o_load_scene;
  static std::vector<tLoadSceneCallback> load_scene_callbacks;

 public:
  SceneLoadObserver();

  static uint64_t detour(void* this_, SSceneInitParameters* scene_init_params);
  static void registerSceneLoadCallback(const tLoadSceneCallback& callback);
};

#endif // __ZHM5RANDOMIZER_SRC_SCENELOADOBSERVER_H__
