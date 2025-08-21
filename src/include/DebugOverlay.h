#pragma once
#include "imgui.h"

namespace NNE::Editor {
	class DebugOverlay {
		public:
			void Init();
			void Render();
			void Shutdown();
	};
} // namespace NNE


