<p align="center">
  <a href="https://github.com/swiftly-solution/swiftly_advertisements">
    <img src="https://cdn.swiftlycs2.net/swiftly-logo.png" alt="SwiftlyLogo" width="80" height="80">
  </a>

  <h3 align="center">[Swiftly] Advertisements</h3>

  <p align="center">
    A simple plugin for Swiftly that sends messages on server at a specified time.
    <br/>
  </p>
</p>

<p align="center">
  <img src="https://img.shields.io/github/downloads/swiftly-solution/swiftly_advertisements/total" alt="Downloads"> 
  <img src="https://img.shields.io/github/contributors/swiftly-solution/swiftly_advertisements?color=dark-green" alt="Contributors">
  <img src="https://img.shields.io/github/issues/swiftly-solution/swiftly_advertisements" alt="Issues">
  <img src="https://img.shields.io/github/license/swiftly-solution/swiftly_advertisements" alt="License">
</p>

---

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

> [!WARNING]
> Type can be just `center`/`chat`/`console`.

### Configuring the plugin 🧐

* After installing the plugin, you need to add messages in `messages` field.

### Creating A Pull Request 😃

1. Fork the Project
2. Create your Feature Branch
3. Commit your Changes
4. Push to the Branch
5. Open a Pull Request

### Have ideas/Found bugs? 💡
Join [Swiftly Discord Server](https://swiftlycs2.net/discord) and send a message in the topic from `📕╎plugins-sharing` of this plugin!

---