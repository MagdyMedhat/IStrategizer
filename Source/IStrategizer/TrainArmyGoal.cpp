#include "TrainArmyGoal.h"
#include "EntityClassExist.h"
#include "And.h"
#include "Message.h"
#include "DataMessage.h"
#include "GameEntity.h"
#include "DataMessage.h"
#include "GameEntity.h"
#include "GamePlayer.h"
#include "GameType.h"
#include "GoalFactory.h"

using namespace IStrategizer;
using namespace std;

TrainArmyGoal::TrainArmyGoal() : GoalEx(GOALEX_TrainArmy)
{
    _ASSERTE("Do not use this goal it is not ready yet");
    _params[PARAM_Amount] = DONT_CARE;
    _params[PARAM_EntityClassId] = ECLASS_START;
}
//----------------------------------------------------------------------------------------------
TrainArmyGoal::TrainArmyGoal(const PlanStepParameters& p_parameters): GoalEx(GOALEX_TrainArmy, p_parameters)
{
    _ASSERTE("Do not use this goal it is not ready yet");
}
//----------------------------------------------------------------------------------------------
void TrainArmyGoal::InitializePostConditions()
{
    vector<Expression*> m_terms;
    m_terms.push_back(new EntityClassExist(PLAYER_Self, (EntityClassType)_params[PARAM_EntityClassId], DONT_CARE));
    _postCondition = new And(m_terms);
}
//----------------------------------------------------------------------------------------------
bool TrainArmyGoal::SuccessConditionsSatisfied(RtsGame& game)
{
    vector<TID> entities;
    game.Self()->Entities((EntityClassType)_params[PARAM_EntityClassId], entities);
    int entitiesCount = 0;
    int requiredCount = _params[PARAM_Amount];
    
    for (TID unitId : entities)
    {
        GameEntity *pEntity = game.Self()->GetEntity(unitId);
        _ASSERTE(pEntity);
        entitiesCount += pEntity->Attr(EOATTR_State) != OBJSTATE_BeingConstructed ? 1 : 0;
    }

    return entitiesCount >= requiredCount;
}
//----------------------------------------------------------------------------------------------
void TrainArmyGoal::HandleMessage(RtsGame& game, Message* p_msg, bool& p_consumed)
{
    if (p_msg->MessageTypeID() == MSG_EntityCreate)
    {
        EntityCreateMessage* pMsg = static_cast<EntityCreateMessage*>(p_msg);
        _ASSERTE(pMsg && pMsg->Data());

        if (pMsg->Data()->OwnerId != PLAYER_Self)
            return;

        TID entityId = pMsg->Data()->EntityId;
        GameEntity *pEntity = game.Self()->GetEntity(entityId);
        _ASSERTE(pEntity);
        EntityClassType entityType = pEntity->Type();

        if (!game.GetEntityType(entityType)->Attr(ECATTR_IsBuilding))
        {
            PlanStepParameters params;
            m_trainedUnits[entityType]++;
            params[PARAM_EntityClassId] = entityType;
            // TODO: the above code is just a hint it wont work, add LFHD code here
            // after adding ForceDescription parameter
        }
    }
}
//----------------------------------------------------------------------------------------------
vector<GoalEx*> TrainArmyGoal::GetSucceededInstances(RtsGame &game)
{
    /* Learning this goal is not useful until we add ForceDescription parameter
    vector<GoalEx*> succeededInstances(m_succeededInstances);
    m_succeededInstances.clear();
    return succeededInstances;*/

    return vector<GoalEx*>();
}