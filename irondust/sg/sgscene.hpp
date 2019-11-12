// (C) 2019 by CyberViking Softwareschmiede GbR
// All rights reserved.
// -----------------------------------------------------
// created by: armin
// created on: 14.05.2019
// -----------------------------------------------------
// This document contains proprietary information belonging to
// CyberViking Softwareschmiede GbR.
// Passing on and copying of this document, use and communication
// of its contents is not permitted without prior written authorization.


#ifndef SGSCENE_HPP
#define SGSCENE_HPP

#include <irondust/sg/sgcontext.hpp>

#include <vector>


namespace irondust
{
    namespace sg
    {
        class ISGNode;
        class ISGResourceNode;

        class SGScene
        {
        public:
            SGScene(ISGNode* root=nullptr);
            virtual ~SGScene();

            ISGNode& getRoot();
            SGContext& getContext();

            void record(ISGResourceNode* res);
            bool init();
            void render();

        private:
            SGContext context;
            ISGNode* root;
            std::vector<ISGResourceNode*> resources;
        };
    }
}

#endif // SGSCENE_HPP
