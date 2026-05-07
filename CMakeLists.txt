cmake_minimum_required(VERSION 4.2)
project(IE_UBB_AN_I_2025_2026_OOP_SEMINAR_3_WAVE_)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(IE_UBB_AN_I_2025_2026_OOP_SEMINAR_3_WAVE_
        DynamicArray.h
        DynamicArray.tpp
        main.cpp
        Rickroll.cpp
        Rickroll.h
        Wave.cpp
        Wave.h
        Silence.cpp
        Silence.h "MorseEncoder.cpp" "SignalProcessor.h" "SignalProcessor.cpp"  "Repository/massage.h" "Repository/massage.cpp" "Repository/Repo.h" "Repository/Repo.cpp")
