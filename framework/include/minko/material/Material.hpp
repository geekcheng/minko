/*
Copyright (c) 2013 Aerys

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

#pragma once

#include "minko/Common.hpp"

#include "minko/data/ArrayProvider.hpp"
#include "minko/render/Blending.hpp"
#include "minko/render/CompareMode.hpp"
#include "minko/render/StencilOperation.hpp"
#include "minko/render/TriangleCulling.hpp"

namespace minko
{
	namespace material
	{
		class Material :
			public data::ArrayProvider
		{
		public:
			typedef std::shared_ptr<Material>					Ptr;

		private:
			typedef std::shared_ptr<render::AbstractTexture>	AbsTexturePtr;
			typedef std::shared_ptr<render::States>				RenderStatesPtr;

		private:
			static const RenderStatesPtr						_defaultStates;

		public:
			inline static
			Ptr
			create()
			{
				return std::shared_ptr<Material>(new Material());
			}

			inline static
			Ptr
			create(Ptr source)
			{
				auto mat = create();

				mat->copyFrom(source);

				return mat;
			}

			Ptr
			blendingMode(render::Blending::Source, render::Blending::Destination);

			Ptr
			blendingMode(render::Blending::Mode);

			render::Blending::Source
			blendingSourceFactor() const;

			render::Blending::Destination
			blendingDestinationFactor() const;

			Ptr
			colorMask(bool);

			bool
			colorMask() const;

			Ptr
			depthMask(bool);

			bool
			depthMask() const;

			Ptr
			depthFunction(render::CompareMode);

			render::CompareMode
			depthFunction() const;

			Ptr
			triangleCulling(render::TriangleCulling);

			render::TriangleCulling
			triangleCulling() const;

			Ptr
			stencilFunction(render::CompareMode);

			render::CompareMode
			stencilFunction() const;

			Ptr
			stencilReference(int);

			int
			stencilReference() const;

			Ptr
			stencilMask(uint);

			uint
			stencilMask() const;

			Ptr
			stencilFailOperation(render::StencilOperation);

			render::StencilOperation
			stencilFailOperation() const;

			Ptr
			stencilDepthFailOperation(render::StencilOperation);

			render::StencilOperation
			stencilDepthFailOperation() const;

			Ptr
			stencilDepthPassOperation(render::StencilOperation);

			render::StencilOperation
			stencilDepthPassOperation() const;

			Ptr
			priority(float);

			float 
			priority() const;

			Ptr
			zSorted(bool);

			bool
			zSorted() const;

			Ptr
			isTransparent(bool transparent, bool zSort = false);

			Ptr
			target(AbsTexturePtr);

			AbsTexturePtr
			target() const;

		protected:
			Material();
		};
	}
}
