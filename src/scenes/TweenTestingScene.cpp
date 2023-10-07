//
// Created by Arya Rakha on 10/1/2023.
//

#include "TweenTestingScene.h"
#include "../systems/ui/SFMLTextSystem.h"
#include "../systems/SFMLSpriteSystem.h"
#include "../systems/tween/TweenSystems.h"
#include "../systems/tween/SFMLTweenSystems.h"
#include "../systems/EntityRelationSystem.h"
#include "../systems/SFMLRenderSystem.h"
#include "../components/WorldPosition.h"
#include "../components/Sprite.h"
#include "../components/Rotation.h"
#include "../util/Random.h"
#include "imgui.h"
#include "../datatype/Ease.h"
#include "../application/Application.h"
#include "../util/Tweens.h"

struct TweenTest{ };

void TweenTestingScene::RegisterSystems(SystemsHandler *handle) {
    Tween::RegisterSystems(handle);
    Tween::RegisterSFMLSystems(handle);

    handle->Register(new EntityRelationSystem());
    handle->Register(new SFMLRenderSystem());
    handle->Register(new SFMLSpriteSystem());
    handle->Register(new SFMLTextSystem());
}

void TweenTestingScene::OnStart() {
    sfWindow = std::dynamic_pointer_cast<SFMLWindow>(window);

    auto bg = registry.create();

    registry.emplace<WorldPosition>(bg, WorldPosition {Vector2(0, 0)});
    registry.emplace<SpriteDefinition>(bg, SpriteDefinition {
            .spriteName =  "darkPurple", .initialOrder =  -10000,
            .useCustomDimensions = true, .customWidth = sfWindow->width, .customHeight = sfWindow->height,
            .tiled = true
    });

    for (int i = 0; i < 1000; ++i) {
        auto testEntity = registry.create();

        registry.emplace<TweenTest>(testEntity);
        registry.emplace<SpriteDefinition>(testEntity, SpriteDefinition {
                .spriteName =  "asteroid-medium-2", .initialOrder =  i,
                .useCustomDimensions = true, .customWidth = 10, .customHeight = 10,
        });
        registry.emplace<Rotation>(testEntity, Rotation{Random::Range(0.f, 360.f)});

        float hw = sfWindow->width / 2.f;
        float hh = sfWindow->height / 2.f;
        float randX = Random::Range(-hw, hw);
        float randY = Random::Range(-hh, hh);
        registry.emplace<WorldPosition>(testEntity, WorldPosition {Vector2(randX, randY)});
    }
}

const char* TypeNames[] = {
        "Linear",
        "InSine", "OutSine", "InOutSine",
        "InQuad", "OutQuad", "InOutQuad",
        "InCubic", "OutCubic", "InOutCubic",
        "InQuart", "OutQuart", "InOutQuart",
        "InQuint", "OutQuint", "InOutQuint",
        "InExpo", "OutExpo", "InOutExpo",
        "InCirc", "OutCirc", "InOutCirc",
        "InBack", "OutBack", "InOutBack",
        "InElastic", "OutElastic", "InOutElastic",
        "InBounce", "OutBounce", "InOutBounce"
};

Ease::Type currentType = Ease::Type::Linear;

void TweenTestingScene::OnUpdate() {
    ImGui::SetNextWindowSize(ImVec2(300, 600), ImGuiCond_FirstUseEver);

    static bool windowOpen;
    if (!ImGui::Begin("Tween Testing", &windowOpen)){
        ImGui::End();
        return;
    }

    static int currentTypeIdx = 0;

    if (ImGui::Button("Reset Scene")){
        ImGui::End();

        Application::ChangeScene<TweenTestingScene>();
        return;
    }

    ImGui::Spacing();

    if (ImGui::Button("Spawn 1000")){
        ImGui::End();

        for (int i = 0; i < 1000; ++i) {
            auto testEntity = registry.create();

            registry.emplace<TweenTest>(testEntity);
            registry.emplace<SpriteDefinition>(testEntity, SpriteDefinition {
                    .spriteName =  "asteroid-medium-2", .initialOrder =  i,
                    .useCustomDimensions = true, .customWidth = 10, .customHeight = 10,
            });
            registry.emplace<Rotation>(testEntity, Rotation{Random::Range(0.f, 360.f)});

            float hw = sfWindow->width / 2.f;
            float hh = sfWindow->height / 2.f;
            float randX = Random::Range(-hw, hw);
            float randY = Random::Range(-hh, hh);
            registry.emplace<WorldPosition>(testEntity, WorldPosition {Vector2(randX, randY)});
        }

        return;
    }

    if (ImGui::Combo("Type", &currentTypeIdx, TypeNames, IM_ARRAYSIZE(TypeNames))) {
        currentType = static_cast<Ease::Type>(currentTypeIdx);
    }

    static float duration = 1.f;


    static bool randomDuration = false;
    ImGui::Checkbox("Random Duration", &randomDuration);
    static float timeRandMultiplier[2] = {1, 1};

    float finalDuration = duration;
    if (randomDuration)
    {
        ImGui::InputFloat2("Duration Range", timeRandMultiplier);
    } else{
        ImGui::InputFloat("Duration", &duration, 0.01f, 1.f);
    }

    ImGui::Spacing();
    ImGui::Spacing();

    //=============================== POS OFFSET ===================================//
    ImGui::Text("Position Offset");

    static float posOffset[2] = {0, 0};
    ImGui::InputFloat2("To Offset Range", posOffset);

    static bool randomPosOffset = false;
    ImGui::Checkbox("Random Offset", &randomPosOffset);

    if (ImGui::Button("Tween Offset Position")){
        auto entities = registry.view<TweenTest>();
        for (auto [entity] : entities.each()) {
            Vector2 offset{posOffset[0], posOffset[1]};

            if (randomPosOffset){
                offset.x = offset.x * Random::Range(-1.f, 1.f);
                offset.y = offset.y * Random::Range(-1.f, 1.f);
            }

            if (randomDuration) finalDuration = Random::Range(timeRandMultiplier[0], timeRandMultiplier[1]);

            Tween::PositionOffset(&registry, entity, Vector2{0,0}, offset, finalDuration)
                .SetEase(currentType);
        }
    }

    ImGui::Spacing();
    ImGui::Spacing();

    //=============================== POS EXACT ===================================//
    ImGui::Text("Position Exact");

    static float posExact[2] = {0, 0};
    ImGui::InputFloat2("To Exact", posExact);

    if (ImGui::Button("Tween Exact Position")){
        auto entities = registry.view<TweenTest, WorldPosition>();
        for (auto [entity, pos] : entities.each()) {
            Vector2 to{posExact[0], posExact[1]};

            if (randomDuration) finalDuration = Random::Range(timeRandMultiplier[0], timeRandMultiplier[1]);

            Tween::PositionExact(&registry, entity, pos.vector, to, finalDuration)
                    .SetEase(currentType);
        }
    }

    ImGui::Spacing();
    ImGui::Spacing();

    //=============================== SCALE ===================================//
    ImGui::Text("Scale");

    static float scaleFrom = 0;
    static float scaleTo = 1;
    static float scaleFromRand[2] = {0, 0};
    static float scaleToRand[2] = {1, 1};
    static bool randomScale = false;
    ImGui::Checkbox("Random Scale", &randomScale);

    if (randomScale){
        ImGui::InputFloat2("Scale From Range", scaleFromRand);
        ImGui::InputFloat2("Scale To Range", scaleToRand);
    }else{
        ImGui::InputFloat("Scale From", &scaleFrom);
        ImGui::InputFloat("Scale To", &scaleTo);
    }

    if (ImGui::Button("Tween Scale")){
        auto entities = registry.view<TweenTest>();
        for (auto [entity] : entities.each()) {
            float from = randomScale ? Random::Range(scaleFromRand[0], scaleFromRand[1]) : scaleFrom;
            float to = randomScale ? Random::Range(scaleToRand[0], scaleToRand[1]) : scaleTo;

            if (randomDuration) finalDuration = Random::Range(timeRandMultiplier[0], timeRandMultiplier[1]);

            Tween::Scale(&registry, entity, Vector2{from, from}, Vector2{to, to}, finalDuration)
                    .SetEase(currentType);
        }
    }

    ImGui::Spacing();
    ImGui::Spacing();

    //=============================== OPACITY ===================================//
    ImGui::Text("Opacity");

    static float opacityFrom = 1;
    static float opacityTo = 0;
    static float opacityFromRand[2] = {1, 1};
    static float opacityToRand[2] = {0, 0};
    static bool randomOpacity = false;
    ImGui::Checkbox("Random Opacity", &randomOpacity);

    if (randomOpacity){
        ImGui::InputFloat2("Opacity From Range", opacityFromRand);
        ImGui::InputFloat2("Opacity To Range", opacityToRand);
    }else{
        ImGui::InputFloat("Opacity From", &opacityFrom);
        ImGui::InputFloat("Opacity To", &opacityTo);
    }

    if (ImGui::Button("Tween Opacity")){
        auto entities = registry.view<TweenTest>();
        for (auto [entity] : entities.each()) {
            float from = randomOpacity ? Random::Range(opacityFromRand[0], opacityFromRand[1]) : opacityFrom;
            float to = randomOpacity ? Random::Range(opacityToRand[0], opacityToRand[1]) : opacityTo;

            if (randomDuration) finalDuration = Random::Range(timeRandMultiplier[0], timeRandMultiplier[1]);

            Tween::Opacity(&registry, entity, from, to, finalDuration)
                    .SetEase(currentType);
        }
    }

    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::End();
}
