Type discriminator formats for polymorphic JSON configuration

Recommendation

- Prefer using the short type name in `$type` for readability and portability.
  Example:
  ```json
  {
    "$type": "NetdevUserConfig",
    "Id": "n1",
    "Hostfwd": "tcp::2222-:22"
  }
  ```

- The system also accepts the following forms (auto-registered):
  1. Short type name (recommended): `NetdevUserConfig`
  2. Full type name: `QemuRunner.QEMUConfig+NetdevUserConfig`
  3. Assembly-qualified: `QemuRunner.QEMUConfig+NetdevUserConfig, QemuManager`

Notes

- Short names are case-insensitive.
- If you add new concrete polymorphic types, annotate them with `[TypeDiscriminator("ShortName")]`.
- The registry auto-registers the short name, the full name and an assembly-qualified form when scanning the assembly.

Schema guidance

- `Settings.schema.json` includes `TypedNetdevs` and `TypedChardevs` examples and accepts `$type` as a string. Use the short form in authored JSON for clarity.
