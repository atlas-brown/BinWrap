// This file is generated

// Copyright (c) 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef v8_inspector_protocol_Console_h
#define v8_inspector_protocol_Console_h

#include "src/inspector/protocol/Protocol.h"
// For each imported domain we generate a ValueConversions struct instead of a full domain definition
// and include Domain::API version from there.
#include "src/inspector/protocol/Runtime.h"

namespace v8_inspector {
namespace protocol {
namespace Console {

// ------------- Forward and enum declarations.
// Console message.
class ConsoleMessage;
// Wrapper for notification params
class MessageAddedNotification;

// ------------- Type and builder declarations.

// Console message.
class  ConsoleMessage : public Serializable{
    PROTOCOL_DISALLOW_COPY(ConsoleMessage);
public:
    static std::unique_ptr<ConsoleMessage> fromValue(protocol::Value* value, ErrorSupport* errors);

    ~ConsoleMessage() override { }

    struct  SourceEnum {
        static const char* Xml;
        static const char* Javascript;
        static const char* Network;
        static const char* ConsoleApi;
        static const char* Storage;
        static const char* Appcache;
        static const char* Rendering;
        static const char* Security;
        static const char* Other;
        static const char* Deprecation;
        static const char* Worker;
    }; // SourceEnum

    String getSource() { return m_source; }
    void setSource(const String& value) { m_source = value; }

    struct  LevelEnum {
        static const char* Log;
        static const char* Warning;
        static const char* Error;
        static const char* Debug;
        static const char* Info;
    }; // LevelEnum

    String getLevel() { return m_level; }
    void setLevel(const String& value) { m_level = value; }

    String getText() { return m_text; }
    void setText(const String& value) { m_text = value; }

    bool hasUrl() { return m_url.isJust(); }
    String getUrl(const String& defaultValue) { return m_url.isJust() ? m_url.fromJust() : defaultValue; }
    void setUrl(const String& value) { m_url = value; }

    bool hasLine() { return m_line.isJust(); }
    int getLine(int defaultValue) { return m_line.isJust() ? m_line.fromJust() : defaultValue; }
    void setLine(int value) { m_line = value; }

    bool hasColumn() { return m_column.isJust(); }
    int getColumn(int defaultValue) { return m_column.isJust() ? m_column.fromJust() : defaultValue; }
    void setColumn(int value) { m_column = value; }

    std::unique_ptr<protocol::DictionaryValue> toValue() const;
    String serialize() override { return toValue()->serialize(); }
    std::unique_ptr<ConsoleMessage> clone() const;

    template<int STATE>
    class ConsoleMessageBuilder {
    public:
        enum {
            NoFieldsSet = 0,
          SourceSet = 1 << 1,
          LevelSet = 1 << 2,
          TextSet = 1 << 3,
            AllFieldsSet = (SourceSet | LevelSet | TextSet | 0)};


        ConsoleMessageBuilder<STATE | SourceSet>& setSource(const String& value)
        {
            static_assert(!(STATE & SourceSet), "property source should not be set yet");
            m_result->setSource(value);
            return castState<SourceSet>();
        }

        ConsoleMessageBuilder<STATE | LevelSet>& setLevel(const String& value)
        {
            static_assert(!(STATE & LevelSet), "property level should not be set yet");
            m_result->setLevel(value);
            return castState<LevelSet>();
        }

        ConsoleMessageBuilder<STATE | TextSet>& setText(const String& value)
        {
            static_assert(!(STATE & TextSet), "property text should not be set yet");
            m_result->setText(value);
            return castState<TextSet>();
        }

        ConsoleMessageBuilder<STATE>& setUrl(const String& value)
        {
            m_result->setUrl(value);
            return *this;
        }

        ConsoleMessageBuilder<STATE>& setLine(int value)
        {
            m_result->setLine(value);
            return *this;
        }

        ConsoleMessageBuilder<STATE>& setColumn(int value)
        {
            m_result->setColumn(value);
            return *this;
        }

        std::unique_ptr<ConsoleMessage> build()
        {
            static_assert(STATE == AllFieldsSet, "state should be AllFieldsSet");
            return std::move(m_result);
        }

    private:
        friend class ConsoleMessage;
        ConsoleMessageBuilder() : m_result(new ConsoleMessage()) { }

        template<int STEP> ConsoleMessageBuilder<STATE | STEP>& castState()
        {
            return *reinterpret_cast<ConsoleMessageBuilder<STATE | STEP>*>(this);
        }

        std::unique_ptr<protocol::Console::ConsoleMessage> m_result;
    };

    static ConsoleMessageBuilder<0> create()
    {
        return ConsoleMessageBuilder<0>();
    }

private:
    ConsoleMessage()
    {
    }

    String m_source;
    String m_level;
    String m_text;
    Maybe<String> m_url;
    Maybe<int> m_line;
    Maybe<int> m_column;
};


// Wrapper for notification params
class  MessageAddedNotification : public Serializable{
    PROTOCOL_DISALLOW_COPY(MessageAddedNotification);
public:
    static std::unique_ptr<MessageAddedNotification> fromValue(protocol::Value* value, ErrorSupport* errors);

    ~MessageAddedNotification() override { }

    protocol::Console::ConsoleMessage* getMessage() { return m_message.get(); }
    void setMessage(std::unique_ptr<protocol::Console::ConsoleMessage> value) { m_message = std::move(value); }

    std::unique_ptr<protocol::DictionaryValue> toValue() const;
    String serialize() override { return toValue()->serialize(); }
    std::unique_ptr<MessageAddedNotification> clone() const;

    template<int STATE>
    class MessageAddedNotificationBuilder {
    public:
        enum {
            NoFieldsSet = 0,
          MessageSet = 1 << 1,
            AllFieldsSet = (MessageSet | 0)};


        MessageAddedNotificationBuilder<STATE | MessageSet>& setMessage(std::unique_ptr<protocol::Console::ConsoleMessage> value)
        {
            static_assert(!(STATE & MessageSet), "property message should not be set yet");
            m_result->setMessage(std::move(value));
            return castState<MessageSet>();
        }

        std::unique_ptr<MessageAddedNotification> build()
        {
            static_assert(STATE == AllFieldsSet, "state should be AllFieldsSet");
            return std::move(m_result);
        }

    private:
        friend class MessageAddedNotification;
        MessageAddedNotificationBuilder() : m_result(new MessageAddedNotification()) { }

        template<int STEP> MessageAddedNotificationBuilder<STATE | STEP>& castState()
        {
            return *reinterpret_cast<MessageAddedNotificationBuilder<STATE | STEP>*>(this);
        }

        std::unique_ptr<protocol::Console::MessageAddedNotification> m_result;
    };

    static MessageAddedNotificationBuilder<0> create()
    {
        return MessageAddedNotificationBuilder<0>();
    }

private:
    MessageAddedNotification()
    {
    }

    std::unique_ptr<protocol::Console::ConsoleMessage> m_message;
};


// ------------- Backend interface.

class  Backend {
public:
    virtual ~Backend() { }

    virtual DispatchResponse enable() = 0;
    virtual DispatchResponse disable() = 0;
    virtual DispatchResponse clearMessages() = 0;

};

// ------------- Frontend interface.

class  Frontend {
public:
    explicit Frontend(FrontendChannel* frontendChannel) : m_frontendChannel(frontendChannel) { }
    void messageAdded(std::unique_ptr<protocol::Console::ConsoleMessage> message);

    void flush();
    void sendRawNotification(const String&);
private:
    FrontendChannel* m_frontendChannel;
};

// ------------- Dispatcher.

class  Dispatcher {
public:
    static void wire(UberDispatcher*, Backend*);

private:
    Dispatcher() { }
};

// ------------- Metainfo.

class  Metainfo {
public:
    using BackendClass = Backend;
    using FrontendClass = Frontend;
    using DispatcherClass = Dispatcher;
    static const char domainName[];
    static const char commandPrefix[];
    static const char version[];
};

} // namespace Console
} // namespace v8_inspector
} // namespace protocol

#endif // !defined(v8_inspector_protocol_Console_h)
