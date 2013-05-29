<details>
  <summary><?php print $name; ?></summary>
  <ul>
  <?php foreach ($details as $label => $detail) { ?>
    <li><strong><?php print $label; ?>:</strong> <?php print $detail; ?></li>
  <?php } ?>
  </ul>
</details>
