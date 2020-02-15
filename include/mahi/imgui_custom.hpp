#pragma once
#include <imgui.h>
#include <imgui_stdlib.h>
#include <vector>

// mahi-gui custom ImGui
namespace ImGui {

/// Enable Viewports
void EnableViewports();

/// Disable Viewports
void DisableViewports();

/// Begins a fixed size ImGui window (useful for single window apps)
bool BeginFixed(const char* name, const ImVec2& pos, const ImVec2& size, ImGuiWindowFlags flags = 0);

/// Shows a tooltip when an item is hovered for longer than delay
void HoverTooltip(const char* tip, float delay = 1.0f);

/// Begins a disabled section
void BeginDisabled(bool disabled = true, float alpha = 0.25f);

/// Ends a disabled section
void EndDisabled(bool disabled = true);

/// A button that acts like a toggle, dimming itself when disabled
void EnableButton(const char* label, bool* enabled, const ImVec2& size = ImVec2(0,0));

/// A regular button with a color
bool ButtonColored(const char* label, const ImVec4& color, const ImVec2& size = ImVec2(0,0));

/// Linearly remaps float x from [x0 x1] to [y0 y1]
inline float Remap(float x, float x0, float x1, float y0, float y1) {
    return y0 + (x - x0) * (y1 - y0) / (x1 - x0);
}

/// Linearly remaps ImVec2 x from [x0 x1] to [y0 y1]
inline ImVec2 Remap(const ImVec2& x, const ImVec2& x0, const ImVec2& x1, const ImVec2& y0, const ImVec2& y1) {
    ImVec2 out;
    out.x = Remap(x.x, x0.x, x1.x, y0.x, y1.x);
    out.y = Remap(x.y, x0.y, x1.y, y0.y, y1.y);
    return out;
}

///////////////////////////////////////////////////////////////////////////////
// DOUBLES
///////////////////////////////////////////////////////////////////////////////

bool DragDouble(const char* label, double* v, float v_speed = 1.0f, double v_min = 0.0, double v_max = 0.0, const char* format = "%.3f", float power = 1.0f);     // If v_min >= v_max we have no bound
bool DragDouble2(const char* label, double v[2], float v_speed = 1.0f, double v_min = 0.0, double v_max = 0.0, const char* format = "%.3f", float power = 1.0f);
bool DragDouble3(const char* label, double v[3], float v_speed = 1.0f, double v_min = 0.0, double v_max = 0.0, const char* format = "%.3f", float power = 1.0f);
bool DragDouble4(const char* label, double v[4], float v_speed = 1.0f, double v_min = 0.0, double v_max = 0.0, const char* format = "%.3f", float power = 1.0f);
bool DragDoubleRange2(const char* label, double* v_current_min, double* v_current_max, float v_speed = 1.0f, double v_min = 0.0f, double v_max = 0.0f, const char* format = "%.3f", const char* format_max = NULL, float power = 1.0f);

bool SliderDouble(const char* label, double* v, double v_min, double v_max, const char* format = "%.3f", float power = 1.0f);     // adjust format to decorate the value with a prefix or a suffix for in-slider labels or unit display. Use power!=1.0 for power curve sliders
bool SliderDouble2(const char* label, double v[2], double v_min, double v_max, const char* format = "%.3f", float power = 1.0f);
bool SliderDouble3(const char* label, double v[3], double v_min, double v_max, const char* format = "%.3f", float power = 1.0f);
bool SliderDouble4(const char* label, double v[4], double v_min, double v_max, const char* format = "%.3f", float power = 1.0f);

bool InputDouble2(const char* label, double v[2], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
bool InputDouble3(const char* label, double v[3], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);
bool InputDouble4(const char* label, double v[4], const char* format = "%.3f", ImGuiInputTextFlags flags = 0);

///////////////////////////////////////////////////////////////////////////////
// PLOT
///////////////////////////////////////////////////////////////////////////////

struct PlotItem {
    enum Type {
        Line,
        Scatter,
        XBar,
        YBar
    };
    PlotItem();
    bool show;
    Type type;
    std::vector<ImVec2> data;
    ImVec4 color;
    float size; 
};

struct PlotAxis {
    PlotAxis();
    bool showGrid;
    bool showTicks;
    bool showLabels;
    float minimum;
    float maximum;
    int divisions;
    int subDivisions;
    ImVec4 color;
    float zoomRate;
    bool lockMin;
    bool lockMax;
    bool flip;
};

struct PlotInterface {
    PlotInterface();
    PlotAxis xAxis;
    PlotAxis yAxis;
    bool showCrosshairs;
    bool showMousePos;
    bool enableSelection;
    bool enableControls;
    ImVec4 frameColor;
    ImVec4 backgroundColor;
    ImVec4 borderColor;  
    ImVec4 selectionColor;
    // internal state
    bool _dragging;
    bool _selecting;
    ImVec2 _selectStart;
};

bool Plot(const char* label_id, PlotInterface* plot, const PlotItem* items, int nItems, const ImVec2& size = {-1,-1});
bool Plot(const char* label_id, PlotInterface& plot, const std::vector<PlotItem>& items, const ImVec2& size = {-1,-1});

} // namespace ImGui