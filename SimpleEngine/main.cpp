#ifndef UNICODE
#define UNICODE
#endif 
#define _USE_MATH_DEFINES

#include <windows.h>
#include <math.h>
#include <iostream>
// #include "Game.h"
// #include "RedrawGame.h"
// #include "BoxGame.h"
#include "ModelsGame.h"

#include <fbxsdk.h>

int main()
{    
    FbxManager* g_pFbxSdkManager = nullptr;
    
    {
        g_pFbxSdkManager = FbxManager::Create();
    
        FbxIOSettings* pIOsettings = FbxIOSettings::Create(g_pFbxSdkManager, IOSROOT );
        g_pFbxSdkManager->SetIOSettings(pIOsettings);
    }
    
    FbxImporter* pImporter = FbxImporter::Create(g_pFbxSdkManager,"");
    FbxScene* pFbxScene = FbxScene::Create(g_pFbxSdkManager,"");
    
    bool bSuccess = pImporter->Initialize("Models\\car_1.fbx", -1, g_pFbxSdkManager->GetIOSettings() );
    if(!bSuccess)
    {
        printf("Error returned: %s\n\n", pImporter->GetStatus().GetErrorString());
        return E_FAIL;
    }
    
    bSuccess = pImporter->Import(pFbxScene);
    if(!bSuccess) return E_FAIL;
    
    pImporter->Destroy();
    
    FbxNode* pFbxRootNode = pFbxScene->GetRootNode();
    
    if(pFbxRootNode)
    {
        for(int i = 0; i < pFbxRootNode->GetChildCount(); i++)
        {
            FbxNode* pFbxChildNode = pFbxRootNode->GetChild(i);
    
            if(pFbxChildNode->GetNodeAttribute() == NULL)
                continue;
    
            FbxNodeAttribute::EType AttributeType = pFbxChildNode->GetNodeAttribute()->GetAttributeType();
    
            if(AttributeType != FbxNodeAttribute::eMesh)
                continue;
    
            FbxMesh* pMesh = (FbxMesh*) pFbxChildNode->GetNodeAttribute();
    
            FbxVector4* pVertices = pMesh->GetControlPoints();
    
    
            int iControlPointIndex = pMesh->GetPolygonVertex(0, 0);
            printf("Vert: %f\n", (float)pVertices[iControlPointIndex].mData[0]);
            
            // for (int j = 0; j < pMesh->GetPolygonCount(); j++)
            // {
            //     int iNumVertices = pMesh->GetPolygonSize(j);
            //     assert( iNumVertices == 3 );
            //
            //     for (int k = 0; k < iNumVertices; k++)
            //     {
            //         int iControlPointIndex = pMesh->GetPolygonVertex(j, k);
            //
            //         printf("Vert: %f\n", (float)pVertices[iControlPointIndex].mData[0]);
            //         
            //     }
            // }
    
        }
    
    }












    
    // Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
    _CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif
    
    // RedrawGame game(GetModuleHandle(NULL));
    try
    {
        ModelsGame game(GetModuleHandle(NULL));
        if (!game.Initialize())
            return 0;
        
        return game.Run();
    }
    catch(DxException& e)
    {
        MessageBox(nullptr, e.ToString().c_str(), L"HR Failed", MB_OK);
        return 0;
    }
}

