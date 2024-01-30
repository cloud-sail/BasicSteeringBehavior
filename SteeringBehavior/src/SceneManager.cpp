#include "SceneManager.h"

SceneManager::SceneManager() : currentScene_(nullptr) {}

void SceneManager::addScene(const std::string& name, std::unique_ptr<Scene> scene) {
    scenes_[name] = std::move(scene);
}

void SceneManager::switchTo(const std::string& name) {
    auto it = scenes_.find(name);
    if (it != scenes_.end()) {
        currentScene_ = it->second.get();
    }
}

void SceneManager::handleInput(sf::Event event) {
    if (currentScene_) {
        currentScene_->handleInput(event);
    }
}

void SceneManager::update(sf::Time deltaTime) {
    if (currentScene_) {
        currentScene_->update(deltaTime);
    }
}

void SceneManager::render(sf::RenderWindow& window) {
    if (currentScene_) {
        currentScene_->render(window);
    }
}
