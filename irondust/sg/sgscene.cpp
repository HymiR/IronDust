/**
 ** This file is part of the irondust project.
 ** Copyright 2019 CyberViking Softwareschmiede GbR <leghissa@cyber-viking.com>.
 **
 ** This program is free software: you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as
 ** published by the Free Software Foundation, either version 3 of the
 ** License, or (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program.  If not, see <http://www.gnu.org/licenses/>.
 **/


#include <irondust/sg/sgscene.hpp>
#include <irondust/sg/sgnode.hpp>
#include <irondust/sg/isgresourcenode.hpp>


namespace irondust
{
    namespace sg
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
}
