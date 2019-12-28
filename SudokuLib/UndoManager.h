#pragma once
#include <vector>

class invalid_operation : std::exception {};

/*
	Act should be such that can be used for doing and undoing things.
	UndoActManager only contains sequence of acts, it's responsible for their order and doesn't manipulate them directly. 
	Acts logic is external so this is the user task to apply act returned from UndoActManager.
	UndoActManager just keep track of possibilities to undo/redo Act.
*/
template <typename TAct>
class UndoActManager {
public:
	UndoActManager() {}

	UndoActManager(std::initializer_list<TAct> acts) : acts(acts), curActsInd(acts.size() - 1) {}

	void Do(TAct act) {
		if (isUndoState) {
			isUndoState = false;
			int numOfDiscardedActs = acts.size() - (curActsInd + 1);
			for (int i = 0; i < numOfDiscardedActs; i++)
				acts.pop_back();
			
			
			acts.push_back(act);
		}
		else {
			acts.push_back(act);
		}
	}

	//undo when there's no prev acts throws invalid_operation
	TAct Undo() {
		if (!isUndoState) {
			isUndoState = true;
			curActsInd = acts.size() - 1;
		}

		if (curActsInd == -1)
			throw invalid_operation{};

		return acts[curActsInd--];
	}

	//redo if in undostate and there's possibility to redo (element in curActsInd + 1)
	TAct Redo() {
		if (!isUndoState || curActsInd + 1 >= acts.size())
			throw invalid_operation{};

		return acts[++curActsInd];
	}

	bool CanRedo() {
		return isUndoState && (curActsInd + 1 < acts.size());
	}

	bool CanUndo() {
		return (isUndoState && curActsInd != -1) ||
			(!isUndoState && acts.size() != 0);
	}
private:
	std::vector<TAct> acts;
	int curActsInd;		//used only in undostate. index points to next undo act
	bool isUndoState = false;	//begins after undo while there's redo possibility
};