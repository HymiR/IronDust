// (C) 2019 by CyberViking Softwareschmiede GbR
// All rights reserved.
// -----------------------------------------------------
// created by: armin
// created on: 12.05.2019
// -----------------------------------------------------
// This document contains proprietary information belonging to
// CyberViking Softwareschmiede GbR.
// Passing on and copying of this document, use and communication
// of its contents is not permitted without prior written authorization.


#ifndef SGSHADERNODE_HPP
#define SGSHADERNODE_HPP

#include <sgnode.hpp>

#include <initializer_list>


namespace cg
{
	namespace oogl
	{
		class GLSLProgram;
	}


	class SGShaderNode : public SGNode
	{
		typedef SGNode base;

	public:
		SGShaderNode(oogl::GLSLProgram* program, const std::initializer_list<ISGNode*>& children={});

		virtual ~SGShaderNode() override;
		virtual void render(SGContext& context) override;

	private:
		oogl::GLSLProgram* program;
	};
}

#endif // SGSHADERNODE_HPP
