#include "Target.h"
#include "taskbaseouterparams.hpp"

CTarget::CTarget(int li_Level, std::wstring lc_String, CDialogObject *ParentPtr) :
         CTargetBase(li_Level, lc_String,ParentPtr), vpc_TargetDynamics(0)
{
    ((CTaskBase*)ParentPtr)->gc_STargetList.push_back(vs_OutData);
    bc_Name = r("Цель");
    bc_TypeName=bc_Name;
    int li_ObjectLevel = li_Level+1;
    switch (((CTaskBase*)ParentPtr)->gc_IndexList[bi_Number]) {
//    case 0:
//        vpc_TargetDynamics =
//            new CAirDynamics(li_ObjectLevel, bi_Number, lc_String);
//        break;
//    case 1:
//        vpc_TargetDynamics =
//           new CBalDynamics(li_ObjectLevel, bi_Number, lc_String);
//        break;
//    case 2:
//        vpc_TargetDynamics =
//            new CFileDynamics(li_ObjectLevel, bi_Number, lc_String);
//        break;
    default:
        return;
    }
}
CTarget::~CTarget()
{

}
void CTarget::pre_initiate()
{
        //SetPusk();
}
void CTarget::edit()
{
}
void CTarget::SetString()
{
    if (bc__TargetList.size()==1) {
        bc_String = r("");
        vpc_TargetDynamics->bc_String = r("");
    } else {
        char buffer[80];
        sprintf(buffer, "%d", bi_Number+1);
        bc_String = r(buffer);
        vpc_TargetDynamics->bc_String = bc_String;
    }
}

void CreateTarget(int li_Type,CTaskBase* pTask)
{
    int li_Number = pTask->gc_IndexList.size();
    pTask->gc_IndexList.push_back(li_Type);
    char buffer[80];
    sprintf(buffer, "%d", li_Number+1);
    new CTarget(1, r(buffer),pTask);
    ChangeObjects(pTask);
}
void DestroyTarget(int li_Number, CTaskBase *pTask)
{
    CTargetBase* lpc_Target = CTarget::bc__TargetList[li_Number];
    if(dynamic_cast<CTarget*>(lpc_Target)->vpc_TargetDynamics != NULL){
        delete dynamic_cast<CTarget*>(lpc_Target)->vpc_TargetDynamics;
        dynamic_cast<CTarget*>(lpc_Target)->vpc_TargetDynamics = NULL;
    }
    if (lpc_Target) {
        delete lpc_Target;
    }
    pTask->gc_IndexList.erase(pTask->gc_IndexList.begin()+li_Number);
    ChangeObjects(pTask);
}

QString gac_Target_Array[100] =
{
    #include "Target_List.hpp"
    rq("Конец списка целей")
};
