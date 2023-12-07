<br/>
<p align="center">
  <a href="https://github.com/swiftly-solution/swiftly_advertisements">
    <img src="https://media.discordapp.net/attachments/979452783466000466/1168236894652469248/Swiftly_Logo.png?ex=6575f264&is=65637d64&hm=dd2834983bebeab98d7febd44bb3bd20e9aded13ecefac63cc990b222a9d9e9e&=&format=webp&quality=lossless&width=468&height=468" alt="Logo" width="80" height="80">
  </a>

  <h3 align="center">[Swiftly] Advertisements</h3>

  <p align="center">
    A simple plugin for Swiftly that sends messages on server at a specified time.
    <br/>
    <br/>
    <a href="https://github.com/swiftly-solution/swiftly_advertisements/issues">Report Bug</a>
    .
    <a href="https://github.com/swiftly-solution/swiftly_advertisements/issues">Request Feature</a>
  </p>
</p>

![Downloads](https://img.shields.io/github/downloads/swiftly-solution/swiftly_advertisements/total) ![Contributors](https://img.shields.io/github/contributors/swiftly-solution/swiftly_advertisements?color=dark-green) ![Issues](https://img.shields.io/github/issues/swiftly-solution/swiftly_advertisements) ![License](https://img.shields.io/github/license/swiftly-solution/swiftly_advertisements) 

### Installation 👀

1. Download the newest [release](https://github.com/swiftly-solution/swiftly_advertisements/releases).
2. Everything is drag & drop, so i think you can do it!
3. Setup messages in configuration file.

Example:

```json
{
    "messages": [
        {
            "message": "test message - 5 seconds",
            "interval": 5000,
            "type": "chat"
        },
        {
            "message": "test message - 0.5 seconds",
            "interval": 500,
            "type": "chat"
        },
        {
            "message": "test message - 10 seconds",
            "interval": 10000,
            "type": "center"
        }
    ]
}
```

(!) Type can be just `center`/`chat`/`console`.

### Configuring the plugin 🧐

* After installing the plugin, you need to add messages in `messages` field.

### Creating A Pull Request 😃

1. Fork the Project
2. Create your Feature Branch
3. Commit your Changes
4. Push to the Branch
5. Open a Pull Request

### Have ideas? 💡
Join [Swiftly Discord Server](https://discord.gg/ESKNDx2CNB)!
