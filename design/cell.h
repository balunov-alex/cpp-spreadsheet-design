#pragma once

#include "common.h"
#include "formula.h"

#include <unordered_set>

class Cell : public CellInterface {
public:     
    Cell(Sheet& sheet);
    ~Cell();

    void Set(std::string text);
    void Clear();

    Value GetValue() const override;
    std::string GetText() const override;

    std::vector<Position> GetReferencedCells() const override;  

private:
    bool WillCauseCircularDependency(const Impl& impl_temp) const;
    void InvalidateCache();

    class Impl;
    class EmptyImpl;
    class TextImpl;
    class FormulaImpl;
    std::unique_ptr<Impl> impl_;

    Sheet& sheet_;
    // Указатели на ячейки, от которых зависит эта ячейка (для отслеживания кольцевых зависимостей)
    std::unordered_set<Cell*> dependencies_cells;
    // Указатели на ячейки, которые зависят от этой ячейки (для инвалидации кэша)
    std::unordered_set<Cell*> dependents_cells;
};
