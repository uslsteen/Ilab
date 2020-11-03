//
// Created by anon on 03.11.2020.
//

#ifndef TRIANGLES_UPD_OCTONODE_H
#define TRIANGLES_UPD_OCTONODE_H

template <typename Data>
class Octonode
{
    Octonode* parent;

    Octonode* childs[8];

    Bnding_region region;

    //Triangles there are
    vector<Data> objects;

};

#endif //TRIANGLES_UPD_OCTONODE_H
