/*
 * Copyright (C) 2017 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef IGNITION_GUI_VARIABLEPILL_HH_
#define IGNITION_GUI_VARIABLEPILL_HH_

#include <map>
#include <memory>
#include <string>

#include <ignition/math/Vector2.hh>
#include "ignition/gui/qt.h"
#include "ignition/gui/Export.hh"

namespace ignition
{
namespace gui
{
    // Forward declare private data class
    class VariablePillPrivate;
    class VariablePillContainer;

    /// \brief A pill-shaped label which can be dragged onto other widgets.
    ///
    /// A pill may work on the multi-variable mode, in which case it can contain
    /// other variable pills as children. This should not be confused with a
    /// VariablePillContainer.
    ///
    /// Every pill has an Id, which is a unique global number that is
    /// incremented every time that a pill is created. Every pill
    /// has a string name based on the prefix "variable" and its Id. Also,
    /// a pill has a text that is displayed.
    ///
    /// ## Styling
    ///
    /// It is possible to use custom QSS styles to control the appearance of
    /// a variable pill. A reference style is provided at
    /// include/ignition/gui/style.qss
    ///
    /// Properties:
    ///   * selectedPill: True when pill is selected
    ///   * multiPillChild: True if this pill is currently a child of another
    ///                     pill
    ///   * multiPillParent: True if this pill is currently a parent of another
    ///                      pill
    class IGNITION_GUI_VISIBLE VariablePill : public QFrame
    {
      Q_OBJECT

      /// \brief Constructor.
      /// \param[in] _parent Pointer to a parent widget.
      public: explicit VariablePill(QWidget *_parent = nullptr);

      /// \brief Destructor
      public: virtual ~VariablePill();

      /// \brief Get the unique id of this variable pill.
      /// \return Unique id.
      public: unsigned int Id() const;

      /// \brief Set a unique name for this variable.
      /// \param[in] _name Name of the variable.
      public: void SetName(const std::string &_name);

      /// \brief Get the unique name for this variable.
      /// \return Name for this variable.
      public: std::string Name() const;

      /// \brief Set the text label for this variable pill.
      /// \param[in] _text Text to set the label to.
      public: void SetText(const std::string &_text);

      /// \brief Get the text label for this variable pill.
      /// \return the text label.
      public: std::string Text() const;

      /// \brief Set the parent of this variable pill.
      /// \param[in] _parent Parent variable pill.
      public: void SetParent(VariablePill *_parent);

      /// \brief Get the parent of this variable pill. If this is a multi-
      /// variable pill, the parent is equal to itself.
      /// \return Parent variable pill.
      public: VariablePill *Parent() const;

      /// \brief Set the container which holds this variable pill.
      /// \param[in] _container Container to hold this variable pill.
      public: void SetContainer(VariablePillContainer *_container);

      /// \brief Get the container which holds this variable pill.
      /// \return _container Container that holds this variable pill.
      public: VariablePillContainer *Container() const;

      /// \brief Add a child variable pill. This becomes a multi-variable pill.
      /// \param[in] _variable Child variable pill to add.
      public: void AddVariablePill(VariablePill *_variable);

      /// \brief Remove a child variable pill.
      /// \param[in] _variable Child variable pill to remove.
      public: void RemoveVariablePill(VariablePill *_variable);

      /// \brief Get a child variable pill by its unique name.
      /// \param[in] _name Name of the variable pill.
      /// \return Child variable pill.
      public: VariablePill *VariablePillByName(const std::string &_name);

      /// \brief Get the number of child variable pills.
      /// \return Number of child variable pills.
      public: unsigned int VariablePillCount() const;

      /// \brief Get all child variable pills.
      /// \return a collection of pills.
      public: std::map<unsigned int, VariablePill *> &VariablePills() const;

      /// \brief Set the selected state of this variable pill.
      /// \param[in] _selected True to set the state to be selected.
      public: void SetSelected(const bool _selected);

      /// \brief Return the selected state of this variable pill.
      /// \return Selected state.
      public: bool IsSelected() const;

      /// \brief Check if a point is inside the widget.
      /// \param[in] _pt Point to check.
      /// \return True if the point is inside the widget.
      public: bool ContainsPoint(const ignition::math::Vector2i &_pt) const;

      /// \brief Used to accept drag enter events.
      /// \param[in] _evt The drag event.
      protected: void dragEnterEvent(QDragEnterEvent *_evt) override;

      /// \brief Used to accept drop events.
      /// \param[in] _evt The drop event.
      protected: void dropEvent(QDropEvent *_evt) override;

      /// \brief Qt mouse press event.
      /// \param[in] _event Qt mouse event.
      protected: void mouseMoveEvent(QMouseEvent *_event) override;

      /// \brief Qt mouse move event.
      /// \param[in] _event Qt mouse event.
      protected: void mousePressEvent(QMouseEvent *_event) override;

      /// \brief Set whether to enable multi-variable mode.
      /// \param[in] _enable True to enable multi-variable mode.
      private: void SetMultiVariableMode(const bool _enable);

      /// \brief Helper function to check whether the drag action is valid.
      /// \param[in] _evt The drag event.
      /// \return True if the drag action is valid
      private: bool IsDragValid(const QDropEvent *_evt) const;

      /// \brief Reapply styles, usually called after a dybamic property change.
      private: void Polish();

      /// \brief Qt signal emitted when a child variable pill is added.
      /// \param[in] _id Unique id of the child variable pill.
      /// \param[in] _name Name of variable pill added.
      signals: void VariableAdded(const unsigned int _id,
                                  const std::string &_name);

      /// \brief Qt signal emitted when a child variable pill is removed.
      /// \param[in] _id Name of child variable pill removed.
      signals: void VariableRemoved(const unsigned int _id);

      /// \brief Qt signal emitted when an existing variable pill is moved from
      /// another pill to be a child of this variable pill.
      /// \param[in] _id Unique id of the existing variable pill that is added.
      signals: void VariableMoved(const unsigned int _id);

      /// \brief Qt signal emitted when the variable pill's text has changed.
      /// \param[in] _label New variable label.
      signals: void VariableTextChanged(const std::string &_label);

      /// \brief Empty variable id used to indicate non-existent variable.
      public: static const unsigned int EmptyVariable;

      /// \internal
      /// \brief Private data pointer.
      private: std::unique_ptr<VariablePillPrivate> dataPtr;
    };
}
}
#endif
