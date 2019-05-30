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


#include <sgscene.hpp>
#include <sgnode.hpp>
#include <isgresourcenode.hpp>


namespace cg
{
    SGScene::SGScene(ISGNode* root)
        : context(*this)
        , root((root == nullptr) ? new SGNode() : root)
    {
    }

    SGScene::~SGScene()
    {
        resources.clear(); // the other nodes own and clean them.
        delete root;
    }

    ISGNode& SGScene::getRoot()
    {
        return *root;
    }

    SGContext& SGScene::getContext()
    {
        return context;
    }

    void SGScene::record(ISGResourceNode* res)
    {
        resources.push_back(res);
    }

    bool SGScene::init()
    {
        bool rc = true;
        for (auto* res : resources) {
            rc &= res->init(this->context);
        }

        return rc;
    }

    void SGScene::render()
    {
        root->render(context);
    }
}
