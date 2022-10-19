//LED는 라인트레이서의 방향을 확인하기 위해 임시로 추가한 코드입니다. 
//LED 관련 코드 제거하셔도 무방합니다.

#define maxSpeed 70   //직선 스피드
#define turnSpeed 60  //커브 스피드1
#define lowSpeed 40   //커브 스피드2

#define wheel_1 5  //바퀴
#define wheel_2 6  //바퀴
#define wheel_3 10  //바퀴
#define wheel_4 11  //바퀴


int leftSensor = 0 ;   //적외선 왼쪽 센서 
int middelSensor = 0;  //적외선 가운데 센서
int rightSensor = 0;   //적외선 오른족 센서
int isStop = 0;   //멈출때 사용하는 변수
int isNowMotion = 0;   //현재 모션 1:오른쪽, 2:왼쪽

void setup() {
  pinMode(wheel_1, OUTPUT);      // 출력핀 설정
  pinMode(wheel_2, OUTPUT);
  pinMode(wheel_3, OUTPUT);      // 출력핀 설정
  pinMode(wheel_4, OUTPUT);

  pinMode(7, INPUT);  //흰색 1, 검정 0  //왼쪽
  pinMode(8, INPUT);  //흰색 1, 검정 0  //가운데
  pinMode(9, INPUT);  //흰색 1, 검정 0  //오른쪽

  pinMode(12, OUTPUT);   //LED 방향
  pinMode(13, OUTPUT);   //LED 방향
  Serial.begin(9600);


}

void loop() {
  //직진인경우 12,13번 LED 모두 HIGH
  digitalWrite(12, LOW);  //왼쪽으로 돌때 12번
  digitalWrite(13, LOW);  //오른쪽으로 돌때 13번
  
  leftSensor = digitalRead(7);
  middelSensor = digitalRead(8);
  rightSensor = digitalRead(9);

  if (leftSensor == 1 && rightSensor == 1) {   //왼족 오른쪽 흰색일때(선밖일때)
    if (middelSensor == 1) {  //가운데도 흰색(모두 선 밖에 있는경우)
      if (isNowMotion == 1) {  //기존에 돌던 방향 체크 >> 오른쪽
        turnR();   //오른쪽으로 회전시키기
      } else if (isNowMotion == 2) {   //기존에 돌던 방향 체크  >> 왼쪽
        turnL();   //왼쪽으로 회전시키기
      }
    } else {
      go();    //앞으로 전진
    }

  } else if (leftSensor > 0 && rightSensor < 1) {   //오른쪽 센서위에 검정색인경우
    goright();  //오른족으로 돌면서 가기
    isNowMotion = 1;  //모션변수는 오른쪽이라고 입력
  } else if (leftSensor < 1 && rightSensor > 0) {   //왼쪽 센서위에 검정색인 경우
    goleft();   //왼쪽으로 돌면서 가기
    isNowMotion = 2;   //모션변수는 왼쪽이라고 입력
  } else if (leftSensor == 0 && leftSensor == 0 && rightSensor == 0) {  //센서가 모두 검정색 위나, 라인카을 손으로 잡고 들었을때.    
    isStop++;
    if (isStop > 30) {  //30의 카운트동안 기존 명령 수행
      stop();  //30 이상 (약 0.3초정도) 지속될경우 멈춤
    }
  }

  if (!(leftSensor == 0 && leftSensor == 0 && rightSensor == 0)) {
    isStop = 0;  //isStop 변수 초기화
  }

  Serial.print(digitalRead(7));
  Serial.print("        ");
  Serial.print(digitalRead(8));
  Serial.print("        ");
  Serial.println(digitalRead(9));
}

void go() {
  analogWrite(wheel_1, maxSpeed);
  analogWrite(wheel_2, 0);
  analogWrite(wheel_3, maxSpeed);
  analogWrite(wheel_4, 0);
  Serial.print("go - ");
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

}

void goleft() {
  analogWrite(wheel_1, lowSpeed);
  analogWrite(wheel_2, 0);
  analogWrite(wheel_3, turnSpeed);
  analogWrite(wheel_4, 0);
  Serial.print("goleft - ");
  digitalWrite(12, HIGH);  

}

void goright() {
  analogWrite(wheel_1, turnSpeed);
  analogWrite(wheel_2, 0);
  analogWrite(wheel_3, lowSpeed);
  analogWrite(wheel_4, 0);
  Serial.print("goright - ");

  digitalWrite(13, HIGH);
}

void turnR() {
  analogWrite(wheel_1, turnSpeed);
  analogWrite(wheel_2, 0);
  analogWrite(wheel_3, 0);
  analogWrite(wheel_4, turnSpeed);
  Serial.print("turnR - ");

  digitalWrite(13, HIGH);
}

void turnL() {
  analogWrite(wheel_1, 0);
  analogWrite(wheel_2, turnSpeed);
  analogWrite(wheel_3, turnSpeed);
  analogWrite(wheel_4, 0);
  Serial.print("turnL - ");

  digitalWrite(12, HIGH);
}

void stop() {
  digitalWrite(wheel_1, LOW);
  digitalWrite(wheel_2, LOW);
  digitalWrite(wheel_3, LOW);
  digitalWrite(wheel_4, LOW);
  Serial.print("stop - ");
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
}
