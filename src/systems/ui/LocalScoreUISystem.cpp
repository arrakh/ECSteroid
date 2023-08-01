//
// Created by Arya Rakha on 7/25/2023.
//

#include "LocalScoreUISystem.h"
#include "../../Application.h"
#include "../../components/LocalPlayer.h"
#include "../../components/Score.h"
#include "../../util/Time.h"

float animationTime = 0.6f;
float currentAnimTime = 0.f;

int currentScore = 0;
int targetScore = 0;

void LocalScoreUISystem::Render(entt::registry *registry, sf::RenderTarget *renderTarget) {
    int score = GetAnimatedScore(registry);

    text.setString("Score: " + std::to_string(score));
    auto bounds = text.getLocalBounds();
    text.setOrigin(bounds.left + bounds.width, 0.f);
    text.setPosition(Application::Width - offset.x, 0.f + offset.y);

    auto window = Application::WindowPtr;
    auto originalView = window->getView();
    renderTarget->setView(uiView);

    renderTarget->draw(text);

    renderTarget->setView(originalView);
}

int LocalScoreUISystem::GetAnimatedScore(const entt::registry *registry) const {
    int newTargetScore = GetTargetScore(registry);

    if (newTargetScore != targetScore) {
        // Only update the target score and animation time if there's a change
        targetScore = newTargetScore;
        currentAnimTime = 0.f;
    }

    currentAnimTime += Time::deltaTime();

    if (currentAnimTime >= animationTime) {
        currentScore = targetScore;
    } else {
        float alpha = currentAnimTime / animationTime;
        currentScore = static_cast<int>(currentScore + (targetScore - currentScore) * alpha);
    }

    return currentScore;
}

int LocalScoreUISystem::GetTargetScore(const entt::registry *registry) const {
    int targetScore = 0;
    auto view = registry->view<LocalPlayer, Score>();
    for (auto [entity, score] : view.each()) {
        targetScore = score.value;
    }
    return targetScore;
}

int LocalScoreUISystem::GetRenderOrder() {
    return 500;
}

void LocalScoreUISystem::Load(entt::registry *registry) {
    uiView.reset(sf::FloatRect{0, 0 ,Application::Width ,Application::Height});

    text.setFont(*fontService->Get("ethnocentric"));
    text.setCharacterSize(46);
    text.setString("Score: 0");
    text.setFillColor(sf::Color{255, 255, 255, 255});
}

void LocalScoreUISystem::Unload() {

}

void LocalScoreUISystem::LocateServices(std::shared_ptr<ServiceLocator> serviceLocator) {
    fontService = serviceLocator->Locate<SFMLFontService>();
}
