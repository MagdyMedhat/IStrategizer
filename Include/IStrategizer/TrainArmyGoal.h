///> [Serializable]
#ifndef TRAINARMYGOAL_H
#define TRAINARMYGOAL_H

#include "GoalEx.h"

namespace IStrategizer
{
    ///> class=TrainArmyGoal
    ///> parent=GoalEx
    class TrainArmyGoal : public GoalEx
    {
        OBJECT_SERIALIZABLE(TrainArmyGoal);

    public:
        TrainArmyGoal();
        TrainArmyGoal(const PlanStepParameters& p_parameters);
        void HandleMessage(RtsGame& game, Message* p_msg, bool& p_consumed);
        std::vector<GoalEx*> GetSucceededInstances(RtsGame &game);

    protected:
        void InitializePostConditions();
        bool SuccessConditionsSatisfied(RtsGame& game);

    private:
        std::map<EntityClassType, int> m_trainedUnits;
        std::vector<GoalEx*> m_succeededInstances;
    };
}
#endif // TRAINARMYGOAL_H
