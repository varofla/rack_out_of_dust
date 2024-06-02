# Rack Out of Dust 프로젝트

> 치사하게 너만 공기청정기 쓰냐? 서버도 공기청정기 쓸 자격 있다!!
> 

24/7 중노동을 하는 홈랩 서버에게 인권..아니 서권을 마련해주는 프로젝트입니다.

# 구성

- SoC: nRF52840
    - nRF Connect SDK
    - IEEE 802.15.4 (ZigBee)
- 센서
    - 쿨링팬 타코미터 (RPM)
    - PMS7003 미세먼지 센서
    - SHT45 온습도 센서
- 쿨링팬: Noctua NF-F12 industrialPPC-300
- 연동: Zigbee2MQTT → Home Assistant
- 전원: 12 V 어댑터

# 파일

```bash
├── fw : 펌웨어 (nRF Connect SDK)
├── hw
│   ├── 3D printed : 3D 프린팅 외형 파일
│   └── PCB : PCB 거버파일 및 JLCPCB SMT 파일 (v1는 잘못 설계된 파일로, v2 사용
└── sw : Z2M 커스텀 장치 정의 파일
```

# 관련 포스팅

1. [프로젝트 설계](https://www.varofla.com/475c7271-f304-468b-922f-4c4ca632acf4)
2. [외형 설계 및 제작](https://www.varofla.com/e27d810e-9beb-4bba-b57b-e6c40fa9b2bd)
3. [펌웨어 구현 및 Z2M 연결](https://www.varofla.com/62771ae1-a312-4e24-9179-140e787831f7)
4. [PCB 설계 및 최종 조립 (완성)](https://www.varofla.com/93159dcd-b3e2-4ca6-9c15-6a3c6facd333)
