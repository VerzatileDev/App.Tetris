#pragma once

/// <summary>
/// <TITLE>SubSystem</TITLE>
/// 
/// <para>
/// Acts as a Base Type of System for other Systems to inherit from.
/// </para>
/// <note>
/// Forcing all Systems to have an initialize and update function.
/// </note>
/// </summary>
class SubSystem
{
public:
    virtual void initialize() = 0;
    virtual void update() = 0;
};
