import React from "react";

interface SelectProps extends React.SelectHTMLAttributes<HTMLSelectElement> {}

export const Select: React.FC<SelectProps> = (props) => {
  return (
    <select
      className="w-full border rounded px-3 py-2 focus:outline-none focus:ring-2 focus:ring-blue-300"
      {...props}
    />
  );
};
