///> [Serializable]
#ifndef ENTITYCLASSEXIST_H
#define ENTITYCLASSEXIST_H

#include "ConditionEx.h"
#include "CheckEntityObjectAttribute.h"

namespace IStrategizer
{
///> class=EntityClassExist
///> parent=ConditionEx
class EntityClassExist : public ConditionEx
{
	OBJECT_SERIALIZABLE(EntityClassExist);

private:
	std::vector<TID>		_entityObjectIds;
    ///> type=map(pair(int,int))
    Serialization::SMap< EntityObjectAttribute, int >   _entityObjectAttributes;
    ///> type=int
    int                 _similarityThreshold;
	///> type=bool
	bool				_oneUse;
	///> type=bool
	bool				_used;
	bool				_blocking;

public:
                        EntityClassExist() {}
						EntityClassExist(PlayerType p_player, EntityClassType p_unitClassId, int p_amount, 
										 std::map< EntityObjectAttribute,int > p_entityObjectAttributes, 
										 int p_similarityThreshold = ExactSimilarity, bool p_blocking = false);
						EntityClassExist(PlayerType p_player, EntityClassType p_unitClassId, int p_amount, bool p_oneUse = false, bool p_blocking = false);
	bool				MatchesAttributes(int p_entityObjectId);
	vector<TID>		EntityObjectIds() const { return _entityObjectIds; }
	int					GetEntityIdByIndex(int p_index) const { return _entityObjectIds[p_index]; }
	bool				Evaluate();
    void	            Copy(IClonable* p_dest);
	bool				Consume(int p_amount);

protected:
	void InitializeAddressesAux();
	//----------------------------------------------------------------------------------------------
};
}

#endif	// ENTITYCLASSEXIST_H