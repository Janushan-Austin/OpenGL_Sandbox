#pragma once
//included for debugging reasons
#include <iostream>


//simple implementation of C# event type
template <class returnType, class ...params>
class Event {
public:
	typedef returnType(*eventFuncType)(params...);

	Event() {
		Size = 10;
		NumSubscribers = 0;
		NumParams = sizeof...(params);
		eventSubcribers = new eventFuncType[Size];
		std::cout << sizeof...(params) << std::endl;
	}

	Event(const Event& eventRef) {
		copyEvent(eventRef);
	}

	void copyEvent(const Event& copy) {

		if (this == &copy) {
			return;
		}

		if (eventSubcribers != NULL) {
			DestroyEvent();
		}

		if (copy.eventSubcribers != NULL) {
			Size = copyEvent.Size;
			NumSubscribers = copyEvent.NumSubcribers;

			eventSubcribers = new eventFuncType[Size];

			for (int i = 0; i < NumSubscribers; i++) {
				eventSubcribers[i] = copy.eventSubcribers[i];
			}
		}
	}

	~Event() {
		DestroyEvent();
	}

	void DestroyEvent() {
		if (eventSubcribers != NULL) {
			delete[] eventSubcribers;
		}
		Size = NumSubscribers = 0;
	}

	const eventFuncType& operator +=(const eventFuncType& func) {
		if (eventSubcribers == NULL && NumSubscribers == Size) {
			Size *= 2;

			eventFuncType* tempHolder = eventSubcribers;
			eventSubcribers = new eventFuncType[Size];

			for (int i = 0; NumSubscribers; i++) {
				eventSubcribers = tempHolder;
			}

			delete [] tempHolder;
		}

		if (Find(func) >= NumSubscribers) {
			eventSubcribers[NumSubscribers] = func;
			NumSubscribers++;
		}

		return func;
	}

	const eventFuncType& operator -=(const eventFuncType& func) {
		for(unsigned int i = 0; i < NumSubscribers; i++) {
			if (eventSubcribers[i] == func) {
				NumSubscribers--;
				eventSubcribers[i] = eventSubcribers[NumSubscribers];
				break;
			}
		}

		return func;
	}

	unsigned int Find(const eventFuncType& func) {
		for (unsigned int i = 0; i < NumSubscribers; i++) {
			if (eventSubcribers[i] == func) {
				return i;
			}
		}

		return NumSubscribers;
	}

	void Invoke(params... args) {
		for (int i = 0; i < NumSubscribers; i++) {
			eventSubcribers[i](args...);
		}
	}

	void operator () (params... args) {
		for (int i = 0; i < NumSubscribers; i++) {
			eventSubcribers[i](args...);
		}
	}

	eventFuncType& operator[](int index) {
		if (index < NumSubscribers) {
			return eventSubcribers[index];
		}
		return nullptr;
	}

private:

	eventFuncType* eventSubcribers;


	unsigned int Size, NumSubscribers, NumParams;
};