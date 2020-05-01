#pragma once

//simple implementation of C# event type
template <class type, class ...types>
class Event {
public:
	typedef type(*eventFuncType)(types...);

	Event() {
		Size = 10;
		NumSubscribers = 0;
		NumParams = sizeof...(types);
		eventSubcribers = new eventFuncType[Size];
		std::cout << sizeof...(types) << std::endl;
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

	const eventFuncType& operator +=(const eventFuncType func) {
		if (eventSubcribers == NULL && NumSubscribers == Size) {
			Size *= 2;

			eventFuncType* tempHolder = eventSubcribers;
			eventSubcribers = new eventFuncType[Size];

			for (int i = 0; NumSubscribers; i++) {
				eventSubcribers = tempHolder;
			}

			delete [] tempHolder;
		}

		eventSubcribers[NumSubscribers] = func;
		NumSubscribers++;

		return func;
	}

	const eventFuncType& operator -=(eventFuncType func) {
		for(int i = 0; i < NumSubscribers; i++) {
			if (eventSubcribers[i] == func) {
				NumSubscribers--;
				eventSubcribers[i] = eventSubcribers[NumSubscribers];
				break;
			}
		}

		return func;
	}

	void Invoke(types... args) {
		for (int i = 0; i < NumSubscribers; i++) {
			eventSubcribers[i](args...);
		}
	}

	void operator () (types... args) {
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