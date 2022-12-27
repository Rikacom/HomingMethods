#ifndef TargetH
#define TargetH
#include "Global.h"
#include "MyTarget.h"
#include "targetexchange.hpp"
#include "Cp_types.h"
/**
 * @brief The CTarget class
 */
class CTarget : public CTargetBase
{
public:

    /**
     * @brief CTarget Класс содержащий экземпляры цели
     * @param li_Level
     * @param lc_String
     * @param ParentPtr
     */
    CTarget(int li_Level, std::wstring lc_String, CDialogObject *ParentPtr=0);
    /**
     * @brief ~CTarget
     */
    virtual ~CTarget();
    /**
     * @brief SetString
     */
    void SetString();
    /**
     * @brief CreateTarget
     * @param li_Type
     * @param pTask
     */
    static void CreateTarget(int li_Type, CTaskBase *pTask);
    ///
    /// \brief DestroyTarget
    /// \param li_Number
    /// \param pTask
    ///
    static void DestroyTarget(int li_Number, CTaskBase* pTask);
    static void ChangeObjects(CTaskBase * pTask);
    void edit();
    void pre_initiate();
    CDynamicsBase* vpc_TargetDynamics;
private:
    /**
     * @brief vs_OutData
     */
    CTargetParamsPtrs vs_OutData;
};
void CreateTarget(int li_Type, CTaskBase *pTask);
void DestroyTarget(int li_Number,CTaskBase* pTask);



#endif
