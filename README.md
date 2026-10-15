## **Plasma spraying video analysis application**

An application based on **CPP**, **OpenCV2**, and **SDL3** designed for analyzing high-speed video footage of plasma spraying processes (calculating characteristics of various flow components).

<a href="diary/about/state_1.png"><img src="diary/about/state_1.png" alt="State 1" border="0" /></a>

___


### More information is available inside the [diary](https://github.com/dimakomplekt/PSMVA/tree/main/diary) 📓

___

## **Workflow**


### The app allows you to select files and their metadata

<a href="diary/about/state_2.png"><img src="diary/about/state_2.png" alt="State 1" border="0" /></a>

### Then it allows to configure OpenCV masks

<a href="diary/about/state_3.png"><img src="diary/about/state_3.png" alt="State 1" border="0" /></a>

### It accepts videos with frames like this one

<a href="https://ibb.co/jk8RWYtb"><img src="https://i.ibb.co/hFgfZN0L/1.png" alt="1" border="0" /></a>


### Then it processes frames and generates a report with following format


| Parameter                                     | Mode 1  | Mode 2  |   ...   | Mode N  |
|-----------------------------------------------|---------|---------|---------|---------|
| Radiation intensity, %                        |         |         |         |         |
| Delta radiation intensity, % / frame          |         |         |         |         |
| Jet width, mm                                 |         |         |         |         |
| Jet length, mm                                |         |         |         |         |
| Main trajectory angle, °                      |         |         |         |         |
| Deviation angle, °                            |         |         |         |         |
| Maximum deviation angle, °                    |         |         |         |         |
| Delta deviation angle, ° / frame              |         |         |         |         |
| Velocity of particles without deviation, m/s  |         |         |         |         |
| Velocity of deviated particles, m/s           |         |         |         |         |
| Delta particle velocity, (m/s) / frame        |         |         |         |         |
| Percentage of deviated particles, %           |         |         |         |         |

___

## Interesting features

1. **`cv::Mat` to `SDL_Texture` translator** – A custom bridge implementation for seamless conversion and rendering between OpenCV images and SDL3 textures.
  
   📂: [`libs/engine/special/opencv_to_sdl`](libs/engine/special/opencv_to_sdl) 

2. **Simplified Hungarian Algorithm** – A lightweight, custom-tailored implementation of the Hungarian method optimized for tracking flow components and tracking particles across video frames.  
   
   📂: [`libs/program_logic/program_states/states_logic/1.3_FLOW_PARAMETERS_CALCULATION`](libs/program_logic/program_states/states_logic/1.3_FLOW_PARAMETERS_CALCULATION)


___

## How to use it by yourself

### ONLY WINDOWS

### 1. Build and Run

To run the application, configure the toolchain (just **MSVC** and **OpenCV5**) on your PC according to the requirements specified in the `CMakeLists.txt` file. You can automate the building and launching process by executing the provided script:

```powershell
./run.ps1
```

### 2. Algorithm Configuration
For proper and accurate tracking performance, you need to adaptively tweak the configuration coefficients within the setup section of the `processing_3_data` structure. 

The configuration struct is located in 📂: 

[`libs/program_logic/program_states/states_logic/1.3_FLOW_PARAMETERS_CALCULATION/1.3_FLOW_PARAMETERS_CALCULATION.h`](libs/program_logic/program_states/states_logic/1.3_FLOW_PARAMETERS_CALCULATION/1.3_FLOW_PARAMETERS_CALCULATION.h)

Modify the parameters inside the **`// ===== Setup =====`** block to match your specific video and experiment conditions:

```cpp
// 3rd mask processing output ctx
struct processing_3_data
{

    // ===== Setup =====


    // Right-side frame zones used for extreme particle detection

    // Zone where we search N + 1 point

    float zone_2_x_min_c = 0.85;  // zone_2: x > 0.85 * frame_width
    float zone_2_x_max_c = 1.0;   // zone_2: x < 1.0 * frame_width

    // Delta from N + 1 point to N point
    float zone_1_x_min_c_delta = 0.02;
    float zone_1_x_max_c_delta = 0.15;

    // Maximum vertical distance from the selected N + 1 point.
    int pixel_spread = 10;


    // Allowed deviation from the main flow direction used for track classification.
    // Checks trigger if the value goes above (100 + X)% or below (95 - X)%.
    float deflection_percentage = 5.0f;

    float minimal_deviation_angle = 3.0f;
    
        
    // Answer characteristics use a median-mean blend.
    // Initial median weight is 0.5.
    // During the study, weights from 0 to 1 with a step of 0.25 will be tested.
    float median_weight = 0.5f;


    // ===== Setup =====
```

### 3. Verification & Expert Mode
You can enable the validation suite by setting the testing macro:

```cpp
#define FPC_TEST_MODE 1
```

When `FPC_TEST_MODE` is enabled, the system runs an analytical comparison. It validates the automatically generated inter-frame particle tracks against the benchmark tracks identified through manual expert evaluation (human brain analysis).
