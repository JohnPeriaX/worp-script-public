# 🏙️ WORP Legacy Archive

> คลังสคริปต์ WORP เวอร์ชันเก่า
> เปิดไว้เพื่อศึกษาโครงสร้าง **PAWN / SA-MP / open.mp** เท่านั้น

![PAWN](https://img.shields.io/badge/Language-PAWN-2f74c0?style=for-the-badge)
![SA-MP](https://img.shields.io/badge/Server-SA--MP-f39c12?style=for-the-badge)
![open.mp](https://img.shields.io/badge/Compatible-open.mp-111111?style=for-the-badge)
![Status](https://img.shields.io/badge/Status-Legacy%20Archive-b91c1c?style=for-the-badge)
![Purpose](https://img.shields.io/badge/Purpose-Study%20Only-16a34a?style=for-the-badge)

---

## 📌 เกี่ยวกับโปรเจกต์

**WORP Legacy Archive** คือสคริปต์ WORP เวอร์ชันเก่าที่ไม่ได้ใช้งานบนเซิร์ฟเวอร์จริงแล้ว

Repository นี้ถูกเปิดไว้เพื่อให้ผู้ที่สนใจสาย **PAWN Developer** ได้ศึกษาแนวทางการวางระบบเซิร์ฟเวอร์
ทั้งด้านโครงสร้าง Gamemode, Components, Include, Plugin และระบบต่าง ๆ ของ SA-MP / open.mp

---

## 🎯 จุดประสงค์

โปรเจกต์นี้เปิดไว้เพื่อ:

- 🧠 ศึกษาโครงสร้างสคริปต์ PAWN ขนาดใหญ่
- 🧩 ดูแนวทางการแยกระบบแบบ Component
- 🛠️ ใช้เป็นตัวอย่างสำหรับผู้พัฒนา SA-MP / open.mp
- 📦 เก็บเป็นประวัติของโปรเจกต์ WORP รุ่นเก่า
- 🌐 ให้ชุมชนสามารถนำไปศึกษาและต่อยอดในแบบของตัวเอง

---

## 🧬 สถานะโปรเจกต์

> ⚠️ สถานะ: **Legacy / Archive / Study Only**

โค้ดใน Repository นี้เป็นโค้ดเก่า
อาจมีบางส่วนที่ล้าสมัย ต้องแก้ Dependency หรือปรับระบบก่อนนำไปใช้งานจริง

ไม่ใช่สคริปต์ที่ถูกเตรียมไว้สำหรับ “โหลดแล้วรันได้ทันที”

---

## 👨‍💻 สำหรับสาย PAWN Dev

เหมาะสำหรับคนที่ต้องการศึกษา:

- ⚙️ การเขียน Gamemode ด้วยภาษา PAWN
- 📁 การแยกระบบเป็นไฟล์ย่อย
- 🧱 การจัด Component ขนาดใหญ่
- 🔌 การใช้งาน Include / Plugin
- 💬 ระบบคำสั่งผู้เล่นและแอดมิน
- 🎒 ระบบ Inventory, Jobs, Dynamic, Groups, Server Core
- 🗂️ แนวทางดูแล Legacy Code ของเซิร์ฟเวอร์จริง

---

## 🧭 โครงสร้างหลัก

```txt
WORP_CITY/
├── gamemodes/       # Gamemode หลัก และ Components
├── filterscripts/   # Filterscript เสริม
├── plugins/         # Plugin สำหรับ Server
├── scriptfiles/     # Runtime Data / ไฟล์ระบบ
├── npcmodes/        # NPC Script
├── logs/            # Server Logs
└── server.cfg       # Config หลักของ Server
