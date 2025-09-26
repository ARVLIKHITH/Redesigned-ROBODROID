# Robodroid — Fire Fighting Robot (First Semester Prototype)  

## Story and Background  
During my first semester at RVCE University, I was enrolled in a 13th Year Certification Course, where I was tasked with designing, prototyping, and presenting a working system.  

While exploring ideas, I came across a [YouTube video demonstration](https://www.youtube.com/watch?v=v19kwZ4ReT0) of a fire-fighting robot. The concept inspired me, and instead of directly replicating it, I decided to experiment with the design, add my own modifications, and build a working version.  

This became Robodroid, my very first robotics prototype.  

- I was responsible for the electronics design, sensor integration, circuit connections, and prototype assembly.  
- My friend, Arnav Bajaj, contributed by developing the Arduino code that handled sensor logic, motor control, and GSM communication.  
- Together, we successfully created a working system capable of detecting fire, sending alerts, and extinguishing flames.  

This project introduced me to embedded systems and robotics, and taught me valuable lessons in power regulation, sensor calibration, and the importance of collaboration.  

ROBODROID
---

<p align="center">
  <img width="600" alt="Robodroid Prototype" src="https://github.com/user-attachments/assets/7fbf0b86-b15a-4936-8327-9096da136ad4" />
</p>


## System Overview  

### Sensors  
- Flame Sensors — used to detect the presence of fire in front of the robot.  
- MQ2 Gas Sensor — detects gases such as propane, methane, and smoke, as well as lighter fumes, within a range of 200–10,000 ppm.  

### Actuators and Components  
- Water Pump — controlled via a relay, used to spray water onto the flame.  
- Servo Motor (180°) — mounted at the front, sweeping the nozzle between 50° and 110° to cover the area of the fire.  
- DC Motors (chassis movement) — allowed the robot to approach the detected fire.  
- SIM800L GSM Module — sent SMS alerts and made phone calls when fire or gas was detected.  

### Controller and Power  
- Arduino UNO — main microcontroller for handling sensors, actuators, and communication.  
- Power Supply — 18650 Li-ion batteries.  
- LM2596 Voltage Regulator — reduced the voltage to ensure the SIM800L module operated safely at around 4.3 V.  

---

## Working Principle  

1. Detection  
   - Flame sensor detects the presence of fire.  
   - MQ2 gas sensor identifies gas or smoke.  

2. Communication  
   - On gas detection, the Arduino sends AT commands to the SIM800L module. The image below shows the message received from the SIM800L under the name Likhith.
    <p align="center">  
     <img width="300" alt="Robodroid Prototype" src="https://github.com/user-attachments/assets/9a1581de-eb0f-4f61-8d08-36c58355ffde" />
</p>

---

<h2 align="center"> Communication Demo </h2>

<p align="center">
  <a href="https://youtu.be/KiAFvgWzrvA">
    <img src="https://img.youtube.com/vi/KiAFvgWzrvA/0.jpg" alt="Robodroid Demo" width="600"/>
  </a>
</p>

<p align="center">
  <a href="https://youtu.be/1N6KJtFeA10">
    <img src="https://img.youtube.com/vi/1N6KJtFeA10/0.jpg" alt="Robodroid Demo" width="600"/>
  </a>
</p>

 - The module sends an SMS and makes a phone call to notify the user.  

3. Action  
   - When fire is detected, the Arduino drives the DC motors to move the robot closer to the fire.  
   - The relay activates the water pump, which sprays water through the nozzle.  
   - The servo motor sweeps the nozzle across an arc to maximise coverage and extinguish the fire.
     
<h2 align="center">Prototype Demo</h2>

<p align="center">
  <a href="https://youtu.be/RUrlLozYwqs">
    <img src="https://img.youtube.com/vi/RUrlLozYwqs/0.jpg" alt="Robodroid Demo" width="600"/>
  </a>
</p>

---

## Contributors  
- Likhith Anand — Electronics design, circuit integration, prototype assembly, power regulation, and documentation.  
- Arnav Bajaj — Arduino programming (sensor logic, motor control, and SIM800L communication).  

---

## Prototype Media  
- [Slides](Fire%20Fighting%20Robot%20Car%20Prototype.pdf)
- [Arduino Code](Fire_Fighting_Bot.ino)
- [Inspiration video](https://www.youtube.com/watch?v=v19kwZ4ReT0)  

---

## Problems Faced (First Semester)  
- Power Issues: The SIM800L module malfunctioned when supplied with more than 5 V. This was resolved using an LM2596 step-down regulator.  
- GSM Reliability: SMS sending and call functions sometimes failed due to unstable AT command handling. Debugging and delays were added for stability.  
- Water Pump Current Draw: The initial current surge from the pump caused the Arduino to reset. This was fixed by isolating the pump on a separate relay-controlled supply.  
- Servo Jitter: The servo motor experienced jittering during idle. Grounding improvements and stable PWM control resolved the issue.  
- Navigation Tuning: Achieving an accurate approach towards the flame required fine adjustments of the flame sensor logic.  

---

## Lessons Learned  
- Proper voltage regulation is critical when using GSM modules like SIM800L.  
- Separating power supplies for high-current actuators and the microcontroller ensures system stability.  
- Sensor calibration significantly improves detection accuracy and reduces false triggers.  
- Teamwork between electronics design and coding is essential in building reliable prototypes.  

---

## References and Inspiration  
- Original Inspiration: [YouTube – Fire Fighting Robot Project](https://www.youtube.com/watch?v=v19kwZ4ReT0).  
- Circuit Diagram Credit: Belongs to the YouTube creator (not my own work).  
- Hardware Guides: Datasheets for the MQ2 sensor, the SIM800L module, and the servo motor.  
- Documentation: Self-prepared presentation and prototype description.  

> Note: Publicly available tutorials inspired this project, but the modifications (SIM800L integration, regulator design, electronics assembly) and the prototype build were my own work, completed in collaboration with Arnav Bajaj.  

---

In the second semester, this design was improved further to address the limitations of the first prototype. 

# Robodroid — Fire Fighting Robot (Second Semester Improvements)  

## Identified Issues in First Prototype  
In the first semester version, the flame detection system relied on individual flame sensors positioned to the left, right, and front. While the robot was able to detect fire within predefined zones, it was unable to accurately **pinpoint the exact location of the flame**. This resulted in:  

- Limited accuracy in navigation towards the fire.  
- Possible overshoot or undershoot of the robot’s movement.  
- Inefficient extinguishing if the fire was not aligned within the predefined detection range.  

---

## Triangulation Method (Second Semester Solution)  
To solve this, during the second semester, we integrated a **triangulation-based detection system** using three flame sensors placed at defined angular offsets. This allowed us to calculate the **position of the flame more precisely** and control the robot’s movement accordingly.  

### Concept  
- Two sensors at known positions (A and B) detect the flame at angles θ₁ and θ₂.  
- By applying trigonometry, the height (d) and distance (L) to the flame can be calculated.  
- This allows the robot to move directly to the detected point, rather than guessing within a predefined zone.

<p align="center">
  <img width="700" alt="image" src="https://github.com/user-attachments/assets/c1e507df-d11d-45a7-b215-57ab67368da6" />
</p>   

### Derivations 

From the geometry of the setup:  

```tan(θ₁) = d / h₁,     tan(θ₂) = d / h₂```  

Equating for d:  

```tan(θ₁) · h₁ = tan(θ₂) · h₂ ``` 

Thus:  

```h₂ = (h₁ · tan(θ₁)) / tan(θ₂)```  

The distance from sensor A to the flame point (BC) can then be derived as:  

```BC = √(d² + h₂²)```  

Alternatively, using a simplified distance formula between the sensors:  

```Distance = (L · tan(θ₁)) / (tan(θ₂) + tan(θ₁))```  

Where:  
- L = distance between the two sensors  
- θ₁, θ₂ = flame detection angles from sensors A and B  
  

Alternatively, using a simplified distance formula between the sensors:  

<p align="center">
  <img src="https://github.com/user-attachments/assets/7d9e7423-4e4d-4dce-8844-bd887b608cc1" alt="Robodroid Prototype" width="500"/>
</p>

## Implementation  
- The three flame sensors were mounted at fixed angular positions.  
- The Arduino collected angle data and, using the above formulas, determined the **precise location of the flame**.  
- The robot’s DC motors were then programmed to move the chassis to this calculated location.  
- Once in range, the water pump and servo-based nozzle system extinguished the flame efficiently.  

---
 <h2>Source Code</h2>
  <a href="https://github.com/ARVLIKHITH/Redesigned-ROBODROID/blob/cedc4c70033ded9adb3d74da09e30fded6b64fe3/Triangulation.ino">
    Triangulation.ino
  
---

## Contributions  
- **Arnav Bajaj** — Designed and derived the triangulation formulas, and implemented the logic in the Arduino code.  
- **Likhith Anand** — Responsible for integrating the modified sensor arrangement, wiring, and testing of the prototype.  

---

## Outcomes of Second Semester Version  
- Robot navigation became **more precise**.  
- Flame detection was no longer limited to predefined zones.  
- The extinguishing process was more effective, as the robot aligned itself directly with the flame’s position.  

---

## References  
- Slide reference for triangulation concept: [Triangulation Method – Slideplayer](./Fire%20Fighting%20Robot%20Car%20Prototype.pdf)
- Self-derived formulas and implementation notes by Arnav Bajaj.

## License  

This repository is licensed under the **MIT License**.  
Please take a look at the [LICENSE](./LICENSE) file for details.  

Note:  
- The license applies to all code, documentation, and prototype work created in this repository by **Likhith Anand** and **Arnav Bajaj**.  
- Third-party content (e.g., external circuit diagrams, inspiration videos) remains the property of its respective creators and is excluded from this license.


