
#include <time.h>
#include <conio.h>
#include <Windows.h>

#include <iostream>

using namespace std;

class NumberPuzzle {
private:
	int SIZE = 2;
	int GAMESIZE = SIZE * SIZE;
	enum { MOVE_UP=0, MOVE_RIGHT, MOVE_DOWN, MOVE_LEFT };
	enum { CTRL_C=0x03, KEY_ESC=0x1B, KEY_UP=0x48, KEY_DOWN=0x50, KEY_LEFT=0x4B, KEY_RIGHT=0x4D };

	bool runFlag = false;

	int *puzzleMap = nullptr;
	int prevX, prevY;
	int posX, posY;

	// 맵 사이즈 설정
	void setSize(int size) {
		if (size <= 1) {
			return;
		}

		this->SIZE = size;
		setMapSize(size * size);
	}

	// 맵 전체 사이즈 설정
	void setMapSize(int size) {
		this->GAMESIZE = size;
	}

	// prevXY 좌표 설정
	void setPrevXY(int posX, int posY) {
		if (posX < 0) {}
		else if ((getSize() - 1) < posX) {}
		else {
			this->prevX = posX;
		}

		if (posY < 0) {}
		else if ((getSize() - 1) < posY) {}
		else {
			this->prevY = posY;
		}
	}

	// prevX 좌표 설정
	void setPrevX(int posX) {
		if (posX < 0) {
			return;
		}
		else if ((getSize() - 1) < posX) {
			return;
		}
		this->prevX = posX;
	}

	// prevY 좌표 설정
	void setPrevY(int posY) {
		if (posY < 0) {
			return;
		}
		else if ((getSize() - 1) < posY) {
			return;
		}
		this->prevY = posY;
	}

	// XY 좌표 설정
	void setPosXY(int posX, int posY) {
		if (posX < 0) {}
		else if ((getSize() - 1) < posX) {}
		else {
			this->posX = posX;
		}

		if (posY < 0) {}
		else if ((getSize() - 1) < posY) {}
		else {
			this->posY = posY;
		}
	}

	// X 좌표 설정
	void setPosX(int posX) {
		if (posX < 0) {
			return;
		}
		else if ((getSize() - 1) < posX) {
			return;
		}
		this->posX = posX;
	}

	// Y 좌표 설정
	void setPosY(int posY) {
		if (posY < 0) {
			return;
		}
		else if ((getSize() - 1) < posY) {
			return;
		}
		this->posY = posY;
	}

	// 맵 할당
	void newMap(int mapSize) {
		if (puzzleMap == nullptr) {
			puzzleMap = new int[mapSize];
			if (puzzleMap == nullptr) {
				cout << "Memory Allocation Error" << endl;
				exit(1);
				return;
			}
		}
		else {
			delete puzzleMap;
			newMap(getMapSize());
		}
	}

	// 맵 가로 or 세로 사이즈 반환
	int getSize() {
		return this->SIZE;
	}

	// 맵 전체 사이즈 반환
	int getMapSize() {
		return this->GAMESIZE;
	}

	// 맵 반환
	int *getMap() {
		return this->puzzleMap;
	}

	// prevX 좌표 반환
	int getPrevX() {
		return this->prevX;
	}

	// prevY 좌표 반환
	int getPrevY() {
		return this->prevY;
	}

	// X 좌표 반환
	int getPosX() {
		return this->posX;
	}

	// Y 좌표 반환
	int getPosY() {
		return this->posY;
	}

	// 게임 플래그 반환
	bool getRunFlag() {
		return this->runFlag;
	}

	// 게임 시작 플래그 설정
	void runGame() {
		this->runFlag = true;
	}

	// 게임 종료 플래그 설정
	void shutGame() {
		this->runFlag = false;
	}

	// x, y 좌표를 pos 좌표로 변경해줌
	int calcPos(int posX, int posY) {
		return posY * getSize() + posX;
	}

	// 맵을 섞음
	void shuffleNumber(int *map, int size, int timesToMix) {
		// (0, 0):0 (1, 0):1, (2, 0):2
		// (0, 1):3 (1, 1):4, (2, 1):5
		// (0, 2):6 (1, 2):7, (2, 2):8

		// 맵 전체 사이즈
		int mapSize = size * size;

		// 맵 섞기
		int pos = mapSize - 1;		// 캐릭터 시작 위치 저장
		int nextDir, prevDir = -1;	// 어디로 움직일지 저장

		int posXY = size;			// X 좌표와 Y 좌표가 같음
		int posX = getPosX();		// X 좌표
		int posY = getPosY();		// Y 좌표
		int prevPos, nowPos;		// 이전 좌표 값, 현재 좌표 값 (스왑 할 때 필요)
		int value = -1;				// 좌표 계산

		for (int i = 0; i < timesToMix; i++) {
			// 다음 행동 예측
			nextDir = rand() % 4;

			// 다음 행동과 이전 행동이 같으면 별로 안좋음
			if (nextDir == prevDir) {
				i--;
				continue;
			}
			// 이전 행동과 다음 행동을 했을 때 상충 되는 행동을 하면 안됨
			else if ((prevDir == MOVE_UP && nextDir == MOVE_DOWN) ||
				(prevDir == MOVE_DOWN && nextDir == MOVE_UP) ||
				(prevDir == MOVE_LEFT && nextDir == MOVE_RIGHT) ||
				(prevDir == MOVE_RIGHT && nextDir == MOVE_LEFT)) {
				i--;
				continue;
			}

			// 이전 행동 저장
			prevDir = nextDir;
			switch (nextDir) {
			case MOVE_UP:
				// Y 좌표가 감소할 경우
				value = max(0, posY - 1);
				if (value != posY) {
					// 이전 좌표와 다음 좌표와 값을 변경 한다.
					prevPos = calcPos(posX, posY);
					nowPos = calcPos(posX, value);
					SWAP(map[nowPos], map[prevPos]);
					// 변경된 위치를 저장
					posY = value;
				}
				else {
					// 갈 수 없는 곳일 경우 다시 방향 예측
					i--;
					continue;
				}
				break;
			case MOVE_DOWN:
				// Y 좌표가 증가할 경우
				value = min(posXY - 1, posY + 1);
				if (value != posY) {
					// 이전 좌표와 다음 좌표와 값을 변경 한다.
					prevPos = calcPos(posX, posY);
					nowPos = calcPos(posX, value);
					SWAP(map[nowPos], map[prevPos]);
					// 변경된 위치를 저장
					posY = value;
				}
				else {
					// 갈 수 없는 곳일 경우 다시 방향 예측
					i--;
					continue;
				}
				break;
			case MOVE_LEFT:
				// X 좌표가 감소할 경우
				value = max(0, posX - 1);
				if (value != posX) {
					// 이전 좌표와 다음 좌표와 값을 변경 한다.
					prevPos = calcPos(posX, posY);
					nowPos = calcPos(value, posY);
					SWAP(map[nowPos], map[prevPos]);
					// 변경된 위치를 저장
					posX = value;
				}
				else {
					// 갈 수 없는 곳일 경우 다시 방향 예측
					i--;
					continue;
				}
				break;
			case MOVE_RIGHT:
				// X 좌표가 증가할 경우
				value = min(posXY - 1, posX + 1);
				if (value != posX) {
					// 이전 좌표와 다음 좌표와 값을 변경 한다.
					prevPos = calcPos(posX, posY);
					nowPos = calcPos(value, posY);
					SWAP(map[nowPos], map[prevPos]);
					// 변경된 위치를 저장
					posX = value;
				}
				else {
					// 갈 수 없는 곳일 경우 다시 방향 예측
					i--;
					continue;
				}
				break;
			}
		}

		// 맵 섞고 난 후 캐릭터 위치 설정
		setPrevXY(posX, posY);
		setPosXY(posX, posY);
	}

	// 맵을 출력한다
	void mapPrint(int *map) {
		int mapSize = getMapSize();
		int maxPos = getSize();

		for (int i = 0; i < mapSize; i++) {
			(map[i] == INT_MAX) ?
				cout << '*' << '\t' : cout << map[i] << '\t';

			if (((i + 1) % maxPos) == 0) {
				cout << endl;
			}
		}

		cout << endl;
	}

	// 설명서 출력
	void helpPrint() {
		cout << "w: 위, s: 아래, a: 왼쪽, d: 오른쪽" << endl;
		cout << "q: 종료" << endl;
	}

	void printGame(int *map) {
		mapPrint(map);
		helpPrint();
	}

public:

	// 스왑 전용
	static void SWAP(int &a, int &b) {
		int temp = a;
		a = b;
		b = temp;
	}

	NumberPuzzle(int size, int timesToMix) {
		// 처음 맵 크기 설정하기
		setSize(size);
		newMap(getMapSize());

		// 캐릭터 좌표 설정
		setPosX(size - 1);
		setPosY(size - 1);

		// 맵 초기화
		initGame(getMap(), timesToMix);

		// 게임 실행 플래그 설정
		runGame();
	}

	~NumberPuzzle() {
		// 메모리 해제 필수! (누수 방지)
		delete puzzleMap;
		puzzleMap = nullptr;
	}

	// 게임 초기화
	void initGame(int *map, int timesToMix) {

		int i;
		int mapSize = getMapSize();
		// 마지막 공백 비우기
		// 이유: 특수한 값을 사용할 것임
		for (i = 0; i < mapSize - 1; i++) {
			map[i] = i + 1;
		}

		// 캐릭터 시작 위치
		map[mapSize - 1] = INT_MAX;

		// 맵 섞기
		int size = getSize();
		shuffleNumber(map, size, timesToMix);
	}

	// 게임 키 입력 받기
	void updateGame(int *map) {
		bool specialKey = false;
		int key = _getch();

		if (key == 0x00 || key == 0xE0) {
			specialKey = true;
			key = _getch();
		}

		int value;					// SWAP을 위한 임시 좌표
		int size = getSize();		// X, Y 최대 좌표
		int posX = getPosX();		// X 좌표
		int posY = getPosY();		// Y 좌표
		bool canMove = false;		// 이동 가능 여부

		//cout << "[현재 위치] " << posX << ", " << posY << endl;

		if (specialKey == false) {
			switch (key) {
			case 'W':
			case 'w':
				// Y 좌표가 감소할 경우
				value = max(0, posY - 1);
				// 이전 좌표와 다음 좌표와 값을 설정 한다.
				if (value != posY) {
					setPrevXY(posX, posY);
					setPosY(value);
					posY = value;
					canMove = true;
				}
				break;
			case 'S':
			case 's':
				// Y 좌표가 증가할 경우
				value = min(size - 1, posY + 1);
				if (value != posY) {
					setPrevXY(posX, posY);
					setPosY(value);
					posY = value;
					canMove = true;
				}
				break;
			case 'A':
			case 'a':
				// X 좌표가 감소할 경우
				value = max(0, posX - 1);
				if (value != posX) {
					setPrevXY(posX, posY);
					setPosX(value);
					posX = value;
					canMove = true;
				}
				break;
			case 'D':
			case 'd':
				// X 좌표가 증가할 경우
				value = min(size - 1, posX + 1);
				if (value != posX) {
					setPrevXY(posX, posY);
					setPosX(value);
					posX = value;
					canMove = true;
				}
				break;
			case 'Q':
			case 'q':
			case KEY_ESC:
			case CTRL_C:
				// 게임 종료 플래그 설정
				shutGame();
				break;
			}
		}
		else {
			switch (key) {
			case KEY_UP:
				// Y 좌표가 감소할 경우
				value = max(0, posY - 1);
				//printf("value: %d, posY: %d\n", value, posY);
				if (value != posY) {
					setPrevXY(posX, posY);
					setPosY(value);
					posY = value;
					canMove = true;
				}
				break;
			case KEY_DOWN:
				// Y 좌표가 증가할 경우
				value = min(size - 1, posY + 1);
				if (value != posY) {
					setPrevXY(posX, posY);
					setPosY(value);
					posY = value;
					canMove = true;
				}
				break;
			case KEY_LEFT:
				// X 좌표가 감소할 경우
				value = max(0, posX - 1);
				if (value != posX) {
					setPrevXY(posX, posY);
					setPosX(value);
					posX = value;
					canMove = true;
				}
				break;
			case KEY_RIGHT:
				// X 좌표가 증가할 경우
				value = min(size - 1, posX + 1);
				if (value != posX) {
					setPrevXY(posX, posY);
					setPosX(value);
					posX = value;
					canMove = true;
				}
				break;
			}
		}

		//cout << "[canMove] " << canMove << endl;
		//cout << "[이동될 위치] " << posX << ", " << posY << endl;
		if (canMove == true) {
			// 현재 좌표와 이전 좌표의 계산을 가져옴
			int prevPos = calcPos(getPrevX(), getPrevY());
			int nowPos = calcPos(getPosX(), getPosY());

			//cout << "[이동될 위치] " << nowPos << " to " << prevPos << endl;

			// 내 위치를 이동 시킴
			SWAP(map[prevPos], map[nowPos]);
		}

		// 마지막으로 게임 끝났는지 확인
		int count = 0;
		int mapSize = getMapSize();
		for (int i = 0; i < mapSize - 1; i++, count++) {
			if (map[i] != (i + 1)) {
				break;
			}
		}

		if (count == (mapSize-1)) {
			system("cls");
			cout << "Congratulation!" << endl;
			cout << "Complete Game..." << endl;
			cout << "Bye~" << endl;
			_getch();
			shutGame();
		}
	}

	void playGame() {
		int *map = getMap();
		
		while (getRunFlag()) {
			printGame(map);
			updateGame(map);
			system("cls");
		}
	}
};

int main(void)
{
	// 랜덤한 숫자 때문에 필요
	srand((unsigned int)time(NULL));

	int count = 3;

	while (true) {
		NumberPuzzle game = NumberPuzzle(count, 10000);
		game.playGame();

		count++;
	}
	return 0;
}