/**
 * \file error.h
 * Essential error signalling and handling functionality
 * 
 * \author Igor Siemienowicz
 * 
 * \copyright Copyright Igor Siemienowicz 2018 Distributed under the Boost
 * Software License, Version 1.0. (See accompanying file ../LICENSE_1_0.txt
 * or copy at https://www.boost.org/LICENSE_1_0.txt
 */

#include <QException>
#include <QMessageBox>

#include <qlib/qlib.h>

#include "logging.h"

#ifndef _gui_error_h_included
#define _gui_error_h_included

/**
 * \brief An exception base-class for use as an error base-class at the GUI
 * level
 */
class Error : public QException
{
    public:

    /**
     * \brief Constructor, initialising the error message
     * 
     * \param msg Human-readable error message
     */
    explicit Error(QString msg) : m_message(std::move(msg)) {}

    /// \cond
    DECLARE_DEFAULT_VIRTUAL_DESTRUCTOR(Error);
    /// \endcond

    /**
     * \brief Throw the error object as an exception
     */
    virtual void raise(void) const override { throw *this; }

    /**
     * \brief Create a cloned copy of the Error object
     * 
     * \return A pointer to a new copy of self, created using `new`
     */
    virtual Error* clone(void) const override
        { return new Error(*this); }

    /**
     * \brief Retrieve the human-readable message for the error
     */
    QString message(void)  const { return m_message; }

    protected:

    QString m_message;  ///< Human-readable message for the error

};  // end Error class

/**
 * \brief Beginning of a top-level TRY/CATCH block for event handlers
 */
#define ACTION_TRY try

/**
 * \brief The end of the top-level try / catch block
 * 
 * This macro catches all exceptions, extracting any information that is
 * available, and displays an appropriate error MessageBox, with the given
 * action description.
 * 
 * \param actionDesc A string describing the action that was being attempted
 * when the error occurred; this is often the same as the menu text
 */
#define ACTION_CATCH_DURING( actionDesc ) \
    catch (const ::Error& err) \
    { \
        logging::logger().log(logging::level_t::error, \
            (QString(actionDesc) + " - " + err.message()).toStdWString()); \
        QMessageBox::critical( \
            this, \
            actionDesc, \
            tr("Error: ") + err.message()); \
    } \
    catch (const QException&) \
    { \
        QString msg(tr("an unrecognised Qt exception was encountered")); \
        logging::logger().log(logging::level_t::error, \
            (QString(actionDesc) + " - " + msg).toStdWString()); \
        QMessageBox::critical( \
            this, \
            actionDesc, \
            tr("Error: ") + msg); \
    } \
    catch (const std::exception& err) \
    { \
        QString msg(err.what()); \
        logging::logger().log(logging::level_t::error, \
            (QString(actionDesc) + " - " + msg).toStdWString()); \
        QMessageBox::critical( \
            this, \
            actionDesc, \
            tr("Error: ") + msg); \
    } \
    catch (...) \
    { \
        QString msg(tr("an unrecognised error condition has arisen; the " \
            "operation could not be completed")); \
        logging::logger().log(logging::level_t::error, \
            (QString(actionDesc) + " - " + msg).toStdWString()); \
        QMessageBox::critical( \
            this, \
            actionDesc, \
            tr("Error: ") + msg); \
    }

#endif
