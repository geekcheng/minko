/*
Copyright (c) 2014 Aerys

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or
substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include "minko/Minko.hpp"
#include "minko/MinkoSDL.hpp"

#include "MyCustomMaterial.hpp"

using namespace minko;
using namespace minko::math;
using namespace minko::component;

const uint WINDOW_WIDTH = 800;
const uint WINDOW_HEIGHT = 600;

int
main(int argc, char** argv)
{
	auto canvas = Canvas::create("Minko Tutorial - Binding the camera", WINDOW_WIDTH, WINDOW_HEIGHT);
	auto sceneManager = component::SceneManager::create(canvas->context());

	sceneManager->assets()->queue("effect/MyCustomEffect.effect");
	auto complete = sceneManager->assets()->complete()->connect([&](file::AssetLibrary::Ptr assets)
	{
		auto root = scene::Node::create("root")
			->addComponent(sceneManager);

		auto camera = scene::Node::create()
			->addComponent(Renderer::create(0x7f7f7fff))
			->addComponent(Transform::create(Matrix4x4::create()->lookAt(Vector3::create(), Vector3::create(-5.0f, 5.0f, 5.0f))))
			->addComponent(PerspectiveCamera::create((float)WINDOW_WIDTH / (float)WINDOW_HEIGHT));
		root->addChild(camera);

		auto myCustomEffect = assets->effect("effect/MyCustomEffect.effect");
		auto myCustomMaterial = material::MyCustomMaterial::create();
		auto cube = scene::Node::create("cube")
			->addComponent(Transform::create(
			Matrix4x4::create()->translation(0.f, 0.f, -5.f)
			))
			->addComponent(Surface::create(
			geometry::CubeGeometry::create(assets->context()),
			myCustomMaterial,
			myCustomEffect
			));
		root->addChild(cube);

		myCustomMaterial->color(Vector4::create(1.f, 0.f, 0.f, 1.f));

		auto enterFrame = canvas->enterFrame()->connect([&](Canvas::Ptr canvas, float t, float dt)
		{
			cube->component<Transform>()->matrix()->prependRotationY(0.01f);

			sceneManager->nextFrame(t, dt);
		});

		canvas->run();
	});

	sceneManager->assets()->load();

	return 0;
}