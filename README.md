# 🏙️ WORP Legacy Archive

> 🧩 คลังสคริปต์ WORP เวอร์ชันเก่า
> สำหรับศึกษาโครงสร้างระบบ **PAWN / SA-MP / open.mp** เท่านั้น

![PAWN](https://img.shields.io/badge/Language-PAWN-blue?style=for-the-badge)
![SA-MP](https://img.shields.io/badge/Server-SA--MP-orange?style=for-the-badge)
![open.mp](https://img.shields.io/badge/Compatible-open.mp-black?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Legacy%20Archive-red?style=for-the-badge)
![Purpose](https://img.shields.io/badge/Purpose-Study%20Only-green?style=for-the-badge)

---

## 📌 เกี่ยวกับโปรเจกต์

Repository นี้คือสคริปต์ **WORP เวอร์ชันเก่า** ที่ไม่ได้ใช้งานจริงแล้ว

เปิดเผยไว้เพื่อเป็นตัวอย่างสำหรับผู้ที่ต้องการศึกษาแนวทางการเขียนระบบเซิร์ฟเวอร์ด้วยภาษา **PAWN**
รวมถึงการจัดโครงสร้าง **Gamemode, Include, Component, Plugin** และระบบต่าง ๆ ภายในเซิร์ฟเวอร์ **SA-MP / open.mp**

---

## 🎯 จุดประสงค์ของ Repository นี้

โปรเจกต์นี้เปิดไว้เพื่อ:

- 🧠 ศึกษาโครงสร้างสคริปต์ PAWN ขนาดใหญ่
- 🧱 ดูแนวทางการแยกระบบเป็น Component
- 🛠️ ใช้เป็นตัวอย่างสำหรับผู้เริ่มต้นหรือผู้พัฒนาเซิร์ฟเวอร์
- 🗂️ เก็บเป็นประวัติของโปรเจกต์ WORP รุ่นเก่า
- 🌐 ให้ชุมชน SA-MP / open.mp นำไปศึกษาและต่อยอดในแบบของตนเอง

---

## 🧬 สถานะของโปรเจกต์

> ⚠️ โปรเจกต์นี้เป็น **Legacy Archive**

หมายถึงเป็นโค้ดเก่าที่ไม่ได้ถูกใช้งานบนเซิร์ฟเวอร์จริงแล้ว

บางระบบอาจล้าสมัย ต้องแก้ไขเพิ่มเติม หรือต้องปรับ Dependency ให้เข้ากับสภาพแวดล้อมปัจจุบันก่อนนำไปใช้งานจริง

---

## 👨‍💻 สำหรับนักพัฒนา PAWN

โค้ดนี้เหมาะสำหรับคนที่ต้องการศึกษา:

- ⚙️ การเขียน Gamemode ด้วยภาษา PAWN
- 📁 การจัดโครงสร้างระบบแบบแยกไฟล์
- 🔌 การใช้งาน Include และ Plugin ต่าง ๆ
- 💬 ระบบคำสั่งผู้เล่น / แอดมิน
- 🎒 ระบบ Jobs, Inventory, Dynamic, Groups และ Server Core
- 🧩 แนวทางการดูแลโปรเจกต์ SA-MP / open.mp ขนาดใหญ่

---

## 🔐 Notice

Repository นี้ **ไม่รวมไฟล์ส่วนตัวหรือไฟล์ใช้งานจริงของเซิร์ฟเวอร์เดิม** เช่น:

- 🔑 Config จริง
- 🗄️ Database จริง
- 🛡️ RCON Password
- 🤖 Token
- 🔗 Webhook
- 🧪 API Key
- 📄 ไฟล์ `.json` / `.yaml` ส่วนตัว
- 🚫 ไฟล์ลับที่เกี่ยวข้องกับเซิร์ฟเวอร์เดิม

กรุณาสร้าง Config และข้อมูลใช้งานจริงของคุณเองจากไฟล์ตัวอย่าง

---

## ⚠️ คำเตือน

สคริปต์นี้เปิดไว้เพื่อการศึกษาเท่านั้น

ไม่แนะนำให้นำไปรันใช้งานจริงทันทีโดยไม่ตรวจสอบ:

- ความปลอดภัยของโค้ด
- Dependency ทั้งหมด
- Plugin ที่ใช้งาน
- Config ส่วนตัว
- ฐานข้อมูล
- ระบบเชื่อมต่อภายนอก

ผู้ใช้งานควรมีพื้นฐานด้าน **PAWN, SA-MP Server, Plugin และระบบฐานข้อมูล** ก่อนนำไปปรับใช้

---

## 🧭 โครงสร้างหลักของโปรเจกต์

```txt
WORP_CITY/
├── gamemodes/       # ไฟล์ Gamemode หลักและ Components
├── filterscripts/   # Filterscript สำหรับระบบเสริม
├── plugins/         # Plugin ที่ใช้กับ Server
├── scriptfiles/     # ข้อมูล Runtime / ไฟล์ระบบ
├── npcmodes/        # NPC Script
├── logs/            # Log ของ Server
└── server.cfg       # Config หลักของ SA-MP Server
