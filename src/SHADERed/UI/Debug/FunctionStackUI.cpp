#include <SHADERed/UI/Debug/FunctionStackUI.h>
#include <imgui/imgui.h>

namespace ed {
	void DebugFunctionStackUI::Refresh()
	{
		std::vector<int> lines = m_data->Debugger.GetFunctionStackLines();

		m_stack.clear();
		spvm_state_t vm = m_data->Debugger.GetVM();
		for (int i = vm->function_stack_current; i >= 0; i--) {
			spvm_result_t func = vm->function_stack_info[i];
			if (func->name && func->name[0] != '@') {
				std::string fname(func->name);
				size_t parenth = fname.find('(');
				if (parenth != std::string::npos)
					fname = fname.substr(0, parenth);

				m_stack.push_back(fname + " @ line " + std::to_string(lines[i]));
			}
		}
	}
	void DebugFunctionStackUI::OnEvent(const SDL_Event& e)
	{
	}
	void DebugFunctionStackUI::Update(float delta)
	{
		for (int i = 0; i < m_stack.size(); i++)
			ImGui::Text(m_stack[i].c_str());
	}
}